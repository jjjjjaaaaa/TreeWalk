#pragma once

#include "ITreeWalk.h"
#include <deque>
#include <unordered_map>
#include <vector>
#include <string>

#include <iostream>
#include <chrono>
#include <iomanip>


class SimpleTreeWalk : public ITreeWalk
{
public:
    SimpleTreeWalk() = default;
    virtual ~SimpleTreeWalk() = default;

    void SetBinaryTree(Node *pRoot) override
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        m_nodeInfo.clear();
        BuildMap(pRoot, 0);
    }

    std::vector<std::string> FindMinPath(int start, int end) override
    {
        auto itStart = m_nodeInfo.find(start);
        auto itEnd = m_nodeInfo.find(end);
        if (itStart == m_nodeInfo.end() || itEnd == m_nodeInfo.end())
        {
            return {};
        }
        auto pStart = itStart->second.first;
        auto pEnd = itEnd->second.first;
        int depthStart = itStart->second.second;
        int depthEnd = itEnd->second.second;

        std::vector<std::string> upPath;
        std::deque<std::string> downPath;

        while (depthEnd > depthStart)
        {
            if (pEnd->m_pParent->m_pLeft == pEnd)
            {
                downPath.push_front(STRING_LEFT);
            }
            else
            {
                downPath.push_front(STRING_RIGHT);
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
                downPath.push_front(STRING_LEFT);
            }
            else
            {
                downPath.push_front(STRING_RIGHT);
            }
            pStart = pStart->m_pParent;
            pEnd = pEnd->m_pParent;
        }

        upPath.insert(upPath.end(), downPath.begin(), downPath.end());
        return upPath;
    }

    std::string GetAlgorithmName() const override
    {
        return "Simple Tree Walk";
    }

    void Clear() override
    {
        m_nodeInfo.clear();
    }

protected:
    void BuildMap(Node *pNode, int depth)
    {
        if (!pNode)
        {
            return;
        }

        m_nodeInfo[pNode->m_val] = {pNode, depth};
        BuildMap(pNode->m_pLeft, depth + 1);
        BuildMap(pNode->m_pRight, depth + 1);
    }

protected:
    std::unordered_map<int, std::pair<Node*, int>> m_nodeInfo;
};