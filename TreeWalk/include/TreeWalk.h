#pragma once

#include "ITreeWalk.h"
#include <unordered_map>

class TreeWalk : public ITreeWalk {
public:
    TreeWalk() = default;
    virtual ~TreeWalk() = default;

    void SetBinaryTree(Node* pRoot) override;
    std::vector<std::string> FindMinPath(int start, int end) override;

protected:
    std::unordered_map<int, Node*> m_valueToNode;
    std::unordered_map<Node*, int> m_nodeDepth;

    void BuildMap(Node* pNode, int depth);
    Node* GetNode(int val) const;
};