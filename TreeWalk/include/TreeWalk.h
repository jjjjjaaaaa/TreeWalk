#pragma once

#include "ITreeWalk.h"
#include <unordered_map>

class TreeWalk : public ITreeWalk {
public:
    TreeWalk() = default;
    virtual ~TreeWalk() = default;

    void SetBinaryTree(Node* pRoot) override;
    std::vector<std::string> FindMinPath(char start, char end) override;    

protected:
    std::unordered_map<char, Node*> m_valueToNode;
    std::unordered_map<Node*, int> m_nodeDepth;

    void BuildMap(Node* pNode, int depth);
    Node* GetNode(char val) const;
};