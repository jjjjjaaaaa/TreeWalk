#pragma once
#include "ITreeWalk.h"
#include <map>
#include <deque>
#include <vector>
#include <string>
#include <unordered_map>

class SimpleParentPointerWalk : public ITreeWalk {
private:
    virtual ~SimpleParentPointerWalk()  = default;

    std::unordered_map<int, Node*> m_node_map;

    void _build_map(Node* u) {
        if (!u) return;
        m_node_map[u->m_val] = u;
        _build_map(u->m_pLeft);
        _build_map(u->m_pRight);
    }

    int _get_depth(Node* n) {
        int d = 0;
        while(n->m_pParent) {
            d++;
            n = n->m_pParent;
        }
        return d;
    }

public:
    std::string GetAlgorithmName() const override {
        return "Simple Parent Pointer Walk";
    }

    void SetBinaryTree(Node* pRoot) override {
        m_node_map.clear();
        _build_map(pRoot);
    }

    std::vector<std::string> FindMinPath(int start_val, int end_val) override {
        if (m_node_map.find(start_val) == m_node_map.end() || m_node_map.find(end_val) == m_node_map.end()) {
            return {};
        }
        Node* start_node = m_node_map[start_val];
        Node* end_node = m_node_map[end_val];

        int d1 = _get_depth(start_node);
        int d2 = _get_depth(end_node);

        std::vector<std::string> up_path;
        std::deque<std::string> down_path;

        while(d1 > d2) {
            up_path.push_back("UP");
            start_node = start_node->m_pParent;
            d1--;
        }
        while(d2 > d1) {
            if(end_node->m_pParent->m_pLeft == end_node) down_path.push_front("LEFT");
            else down_path.push_front("RIGHT");
            end_node = end_node->m_pParent;
            d2--;
        }

        while(start_node != end_node) {
            up_path.push_back("UP");
            start_node = start_node->m_pParent;
            if(end_node->m_pParent->m_pLeft == end_node) down_path.push_front("LEFT");
            else down_path.push_front("RIGHT");
            end_node = end_node->m_pParent;
        }

        up_path.insert(up_path.end(), down_path.begin(), down_path.end());
        return up_path;
    }

    void Clear() override {
        m_node_map.clear();
    }
};