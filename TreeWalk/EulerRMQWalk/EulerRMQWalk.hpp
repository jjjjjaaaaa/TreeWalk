#pragma once
#include "ITreeWalk.h"
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <cmath>

class EulerRMQWalk : public ITreeWalk
{
private:
    Node *m_pRoot = nullptr;
    int m_node_count = 0;
    int m_log_tour_size = 0;

    // 核心資料結構
    std::vector<int> m_euler_tour;
    std::vector<int> m_depth_tour;
    std::vector<int> m_first_occurrence;
    std::vector<std::vector<int>> m_sparse_table;
    std::vector<int> m_node_depths;

    // 輔助映射
    std::map<int, int> m_val_to_id;
    std::map<int, Node *> m_val_to_node;

    void _build_maps(Node *u)
    {
        if (!u || m_val_to_id.count(u->m_val))
            return;
        int u_id = m_node_count++;
        m_val_to_id[u->m_val] = u_id;
        m_val_to_node[u_id] = u;
        _build_maps(u->m_pLeft);
        _build_maps(u->m_pRight);
    }

    void _dfs_tour(Node *u, int d)
    {
        if (!u)
            return;

        int u_id = m_val_to_id[u->m_val];
        m_node_depths[u_id] = d;
        m_first_occurrence[u_id] = m_euler_tour.size();
        m_euler_tour.push_back(u_id);
        m_depth_tour.push_back(d);

        if (u->m_pLeft)
        {
            _dfs_tour(u->m_pLeft, d + 1);
            m_euler_tour.push_back(u_id);
            m_depth_tour.push_back(d);
        }
        if (u->m_pRight)
        {
            _dfs_tour(u->m_pRight, d + 1);
            m_euler_tour.push_back(u_id);
            m_depth_tour.push_back(d);
        }
    }

    int _query_rmq(int l, int r)
    {
        int j = (l == r) ? 0 : floor(log2(r - l + 1));
        if (m_depth_tour[m_sparse_table[j][l]] <= m_depth_tour[m_sparse_table[j][r - (1 << j) + 1]])
        {
            return m_sparse_table[j][l];
        }
        else
        {
            return m_sparse_table[j][r - (1 << j) + 1];
        }
    }

    int _lca(int u, int v)
    {
        int l = m_first_occurrence[u];
        int r = m_first_occurrence[v];
        if (l > r)
            std::swap(l, r);
        int tour_index = _query_rmq(l, r);
        return m_euler_tour[tour_index];
    }

    std::vector<std::string> _reconstructPath(int start_id, int end_id, int lca_id)
    {
        std::vector<std::string> path;
        int up_steps = m_node_depths[start_id] - m_node_depths[lca_id];
        for (int i = 0; i < up_steps; ++i)
        {
            path.push_back("UP");
        }
        std::deque<std::string> down_path;
        Node *curr_node = m_val_to_node[end_id];
        Node *lca_node = m_val_to_node[lca_id];

        while (curr_node != lca_node)
        {
            if (curr_node->m_pParent->m_pLeft == curr_node)
            {
                down_path.push_front("LEFT");
            }
            else
            {
                down_path.push_front("RIGHT");
            }
            curr_node = curr_node->m_pParent;
        }
        path.insert(path.end(), down_path.begin(), down_path.end());
        return path;
    }

public:
    std::string GetAlgorithmName() const override
    {
        return "Euler Tour + RMQ";
    }

    void SetBinaryTree(Node *pRoot) override
    {
        // 1. 清理狀態
        m_pRoot = pRoot;
        m_node_count = 0;
        m_val_to_id.clear();
        m_val_to_node.clear();
        m_euler_tour.clear();
        m_depth_tour.clear();

        if (!pRoot)
            return;

        // 2. 第一次遍歷：建立映射並計算節點總數
        _build_maps(pRoot);

        // 3. 根據節點總數，精準設定 vector 大小
        m_first_occurrence.resize(m_node_count);
        m_node_depths.resize(m_node_count);

        // 4. 第二次遍歷：產生歐拉序列
        _dfs_tour(pRoot, 0);

        // 5. 根據歐拉序列的確切長度，建立稀疏表 (Sparse Table)
        int tour_size = m_euler_tour.size();
        m_log_tour_size = (tour_size == 0) ? 0 : floor(log2(tour_size)) + 1;
        m_sparse_table.assign(m_log_tour_size, std::vector<int>(tour_size));

        for (int i = 0; i < tour_size; ++i)
            m_sparse_table[0][i] = i;

        for (int j = 1; j < m_log_tour_size; ++j)
        {
            for (int i = 0; i + (1 << j) <= tour_size; ++i)
            {
                int idx1 = m_sparse_table[j - 1][i];
                int idx2 = m_sparse_table[j - 1][i + (1 << (j - 1))];
                m_sparse_table[j][i] = (m_depth_tour[idx1] < m_depth_tour[idx2]) ? idx1 : idx2;
            }
        }
    }

    std::vector<std::string> FindMinPath(int start, int end) override
    {
        if (m_val_to_id.find(start) == m_val_to_id.end() || m_val_to_id.find(end) == m_val_to_id.end())
        {
            return {};
        }
        int start_id = m_val_to_id[start];
        int end_id = m_val_to_id[end];
        int lca_id = _lca(start_id, end_id);
        return _reconstructPath(start_id, end_id, lca_id);
    }

    void Clear() override
    {
        m_pRoot = nullptr;
        m_node_count = 0;
        m_euler_tour.clear();
        m_depth_tour.clear();
        m_first_occurrence.clear();
        m_sparse_table.clear();
        m_node_depths.clear();
        m_val_to_id.clear();
        m_val_to_node.clear();
    }
};