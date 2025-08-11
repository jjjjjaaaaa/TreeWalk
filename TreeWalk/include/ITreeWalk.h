#pragma once

#include <string>
#include <vector>
#include <string>

#include "Node.h"

class ITreeWalk
{
public:
    virtual ~ITreeWalk() = default;

    virtual void SetBinaryTree(Node *pRoot) = 0;
    virtual std::vector<std::string> FindMinPath(int start, int end) = 0;
    virtual void Clear() = 0;
    virtual std::string GetAlgorithmName() const = 0;
};
