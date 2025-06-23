#include "TreeWalk.h"

void TreeWalk::BuildMap(Node *pNode, int depth)
{
    if (!pNode)
    {
        return;
    }

    m_valueToNode[pNode->m_val] = pNode;
    m_nodeDepth[pNode] = depth;
    BuildMap(pNode->m_pLeft, depth + 1);
    BuildMap(pNode->m_pRight, depth + 1);
}

Node *TreeWalk::GetNode(char val) const
{
    auto it = m_valueToNode.find(val);
    if (it != m_valueToNode.end())
    {
        return it->second;
    }

    return nullptr;
}

void TreeWalk::SetBinaryTree(Node *pRoot)
{
    m_valueToNode.clear();
    m_nodeDepth.clear();
    BuildMap(pRoot, 0);
}

std::vector<std::string> TreeWalk::FindMinPath(char start, char end)
{
    auto pStart = GetNode(start);
    auto pEnd = GetNode(end);
    if (!pStart || !pEnd) 
    {
        return {};
    }

    if (pStart == pEnd)
    {
        return {};
    }

    std::vector<std::string> upPath, downPath;

    int depthStart = m_nodeDepth[pStart];
    int depthEnd = m_nodeDepth[pEnd];

    while (depthEnd > depthStart)
    {
        if (pEnd->m_pParent->m_pLeft == pEnd)
        {
            downPath.push_back(STRING_LEFT);
        }
        else
        {
            downPath.push_back(STRING_RIGHT);
        }
        pEnd = pEnd->m_pParent;
        depthEnd--;
    }

    while (depthStart > depthEnd)
    {
        upPath.push_back(STRING_UP);
        pStart = pStart->m_pParent;
        depthStart--;
    }

    while (pStart != pEnd)
    {
        upPath.push_back(STRING_UP);
        if (pEnd->m_pParent->m_pLeft == pEnd)
        {
            downPath.push_back(STRING_LEFT);
        }
        else
        {
            downPath.push_back(STRING_RIGHT);
        }
        pStart = pStart->m_pParent;
        pEnd = pEnd->m_pParent;
    }

    upPath.insert(upPath.end(), downPath.rbegin(), downPath.rend());
    return upPath;
}