#pragma once

#include "ITreeWalk.h"
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <cmath>

class BinaryLiftingWalk : public ITreeWalk {
private:
    Node* m_pRoot = nullptr;
    int m_node_count = 0;
    int m_log_node_count = 0;

    // 核心資料結構
    std::vector<std::vector<int>> m_up;
    std::vector<int> m_depth;

    // 輔助映射
    std::map<int, int> m_id_to_id;
    std::map<int, Node*> m_val_to_id;

    // DFS 遍歷以收集初始資訊
    void _dfs(Node* u, int p_id, int d, std::vector<int>& direct_parents) {
        if (!u) return;

        int u_id = m_node_count++;
        m_id_to_id[u->m_val] = u_id;
        m_val_to_id[u_id] = u;

        // 使用 push_back 動態增長
        m_depth.push_back(d);
        direct_parents.push_back(p_id);

        _dfs(u->m_pLeft, u_id, d + 1, direct_parents);
        _dfs(u->m_pRight, u_id, d + 1, direct_parents);
    }

    int _lca(int u, int v) {
        if (m_depth[u] < m_depth[v]) std::swap(u, v);

        // 使用動態計算的 m_log_node_count
        for (int j = m_log_node_count - 1; j >= 0; --j) {
            if (m_depth[u] - (1 << j) >= m_depth[v]) {
                u = m_up[u][j];
            }
        }

        if (u == v) return u;

        for (int j = m_log_node_count - 1; j >= 0; --j) {
            if (m_up[u][j] != -1 && m_up[u][j] != m_up[v][j]) {
                u = m_up[u][j];
                v = m_up[v][j];
            }
        }
        return m_up[u][0];
    }

    std::vector<std::string> _reconstructPath(int start_id, int end_id, int lca_id) {
        // 這個函式無需改動
        std::vector<std::string> path;
        int up_steps = m_depth[start_id] - m_depth[lca_id];
        for (int i = 0; i < up_steps; ++i) {
            path.push_back("UP");
        }
        std::deque<std::string> down_path;
        Node* curr_node = m_val_to_id[end_id];
        Node* lca_node = m_val_to_id[lca_id];
        while (curr_node != lca_node) {
            if (curr_node->m_pParent->m_pLeft == curr_node) {
                down_path.push_front("LEFT");
            } else {
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
        return "Binary Lifting";
    }

    void SetBinaryTree(Node* pRoot) override {
        // 1. 清理狀態，準備重置
        m_pRoot = pRoot;
        m_node_count = 0;
        m_id_to_id.clear();
        m_val_to_id.clear();
        m_depth.clear();
        m_up.clear();

        if (!pRoot) return;

        // 2. 執行一次 DFS 來收集節點數、深度和直接父節點
        std::vector<int> direct_parents;
        _dfs(m_pRoot, -1, 0, direct_parents);

        // 3. DFS 結束後，我們知道了確切的節點數，現在可以初始化 m_up 表格
        m_log_node_count = (m_node_count == 0) ? 0 : floor(log2(m_node_count)) + 1;
        m_up.assign(m_node_count, std::vector<int>(m_log_node_count, -1));

        // 4. 將暫存的父節點資訊回填到 m_up 的第一列
        for (int i = 0; i < m_node_count; ++i) {
            m_up[i][0] = direct_parents[i];
        }

        // 5. 執行動態規劃，填充 m_up 的其餘部分
        for (int j = 1; j < m_log_node_count; ++j) {
            for (int i = 0; i < m_node_count; ++i) {
                if (m_up[i][j - 1] != -1) {
                    m_up[i][j] = m_up[m_up[i][j - 1]][j - 1];
                }
            }
        }
    }

    std::vector<std::string> FindMinPath(int start, int end) override {
        if (m_id_to_id.find(start) == m_id_to_id.end() || m_id_to_id.find(end) == m_id_to_id.end()) {
            return {};
        }
        int start_id = m_id_to_id[start];
        int end_id = m_id_to_id[end];
        int lca_id = _lca(start_id, end_id);
        return _reconstructPath(start_id, end_id, lca_id);
    }

    void Clear() override {
        m_pRoot = nullptr;
        m_node_count = 0;
        m_log_node_count = 0;
        m_up.clear();
        m_depth.clear();
        m_id_to_id.clear();
        m_val_to_id.clear();
    }
};
