#pragma once

#include <string>
#include <vector>

#include "Node.h"

class ITreeWalk {
public: 
    virtual ~ITreeWalk() = default;

    virtual void SetBinaryTree(Node* pRoot) = 0;
    virtual std::vector<std::string> FindMinPath(char start, char end) = 0;
};
