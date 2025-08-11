#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "SimpleTreeWalk/SimpleTreeWalk.hpp"
#include "BinaryLiftingWalk/BinaryLiftingWalk.hpp"
#include "EulerRMQWalk/EulerRMQWalk.hpp"
#include "SimpleParentPointerWalk/SimpleParentPointerWalk.hpp"

struct TestCase
{
    std::string description;
    Node *root;
    int start;
    int end;
    std::vector<std::string> expectedPath;
    TestCase(const std::string &desc, Node *r, int s, int e, const std::vector<std::string> &exp)
        : description(desc), root(r), start(s), end(e), expectedPath(exp) {}
};

auto setParent = [](Node *pParent, Node *pLeft, Node *pRight)
{
    if (pLeft)
        pLeft->m_pParent = pParent;
    if (pRight)
        pRight->m_pParent = pParent;
};

/**
 * @brief 產生一棵一般、不對稱的樹 (General Case)
 *    1
 *   / \
 *  2   3
 *   \ / \
 *   4 5  6
 *       /
 *      7
 */
Node *GetGeneralTree()
{
    static Node *root = nullptr;
    if (root)
        return root;

    // 使用 map 方便管理節點，避免重複 new
    static std::map<int, Node *> nodes;
    for (int i = 1; i <= 7; ++i)
    {
        nodes[i] = new Node(i);
    }

    nodes[1]->m_pLeft = nodes[2];
    nodes[2]->m_pParent = nodes[1];
    nodes[1]->m_pRight = nodes[3];
    nodes[3]->m_pParent = nodes[1];
    nodes[2]->m_pRight = nodes[4];
    nodes[4]->m_pParent = nodes[2];
    nodes[3]->m_pLeft = nodes[5];
    nodes[5]->m_pParent = nodes[3];
    nodes[3]->m_pRight = nodes[6];
    nodes[6]->m_pParent = nodes[3];
    nodes[6]->m_pLeft = nodes[7];
    nodes[7]->m_pParent = nodes[6];

    root = nodes[1];
    return root;
}

/**
 * @brief 產生一棵滿的、完美的二元樹 (Full/Balanced Case)
 *     10
 *    /  \
 *   20   30
 *  / \   / \
 * 40 50 60  70
 */
Node *GetFullTree()
{
    static Node *root = nullptr;
    if (root)
        return root;

    static std::map<int, Node *> nodes;
    int vals[] = {10, 20, 30, 40, 50, 60, 70};
    for (int val : vals)
    {
        nodes[val] = new Node(val);
    }

    nodes[10]->m_pLeft = nodes[20];
    nodes[20]->m_pParent = nodes[10];
    nodes[10]->m_pRight = nodes[30];
    nodes[30]->m_pParent = nodes[10];
    nodes[20]->m_pLeft = nodes[40];
    nodes[40]->m_pParent = nodes[20];
    nodes[20]->m_pRight = nodes[50];
    nodes[50]->m_pParent = nodes[20];
    nodes[30]->m_pLeft = nodes[60];
    nodes[60]->m_pParent = nodes[30];
    nodes[30]->m_pRight = nodes[70];
    nodes[70]->m_pParent = nodes[30];

    root = nodes[10];
    return root;
}

/**
 * @brief 產生一棵退化的「竹竿」樹 (Extreme Case)
 *    100
 *    /
 *   101
 *   /
 *  102
 *  /
 * 103
 */
Node *GetStickTree()
{
    static Node *root = nullptr;
    if (root)
        return root;

    static std::map<int, Node *> nodes;
    for (int i = 0; i < 4; ++i)
    {
        nodes[100 + i] = new Node(100 + i);
    }

    nodes[100]->m_pLeft = nodes[101];
    nodes[101]->m_pParent = nodes[100];
    nodes[101]->m_pLeft = nodes[102];
    nodes[102]->m_pParent = nodes[101];
    nodes[102]->m_pLeft = nodes[103];
    nodes[103]->m_pParent = nodes[102];

    root = nodes[100];
    return root;
}

/**
 * @brief 產生一個只有根節點的樹 (Boundary Case)
 */
Node *GetSingleNodeTree()
{
    static Node *root = new Node(200);
    return root;
}

/**
 * @brief 產生一棵空樹 (Boundary Case)
 */
Node *GetNullTree()
{
    return nullptr;
}

// --- 測試案例陣列 ---

TestCase testCases[] = {
    // --- 一般情況 (General Case) ---
    {"一般樹: B(2) -> F(6)", GetGeneralTree(), 2, 6, {"UP", "RIGHT", "RIGHT"}},
    {"一般樹: D(4) -> E(5)", GetGeneralTree(), 4, 5, {"UP", "UP", "RIGHT", "LEFT"}},
    {"一般樹: G(7) -> B(2)", GetGeneralTree(), 7, 2, {"UP", "UP", "UP", "LEFT"}},
    {"一般樹: E(5) -> F(6) (兄弟節點)", GetGeneralTree(), 5, 6, {"UP", "RIGHT"}},
    {"一般樹: A(1) -> G(7) (從根到葉)", GetGeneralTree(), 1, 7, {"RIGHT", "RIGHT", "LEFT"}},

    // --- 滿的二元樹 (Full Tree Case) ---
    {"滿樹: 40 -> 70 (葉到葉)", GetFullTree(), 40, 70, {"UP", "UP", "RIGHT", "RIGHT"}},
    {"滿樹: 50 -> 60", GetFullTree(), 50, 60, {"UP", "UP", "RIGHT", "LEFT"}},
    {"滿樹: 10 -> 50 (根到孫)", GetFullTree(), 10, 50, {"LEFT", "RIGHT"}},
    {"滿樹: 40 -> 20 (葉到父)", GetFullTree(), 40, 20, {"UP"}},

    // --- 極端情況 (Extreme Case - Stick Tree) ---
    {"竹竿樹: 103 -> 100 (底到頂)", GetStickTree(), 103, 100, {"UP", "UP", "UP"}},
    {"竹竿樹: 100 -> 103 (頂到底)", GetStickTree(), 100, 103, {"LEFT", "LEFT", "LEFT"}},
    {"竹竿樹: 102 -> 101", GetStickTree(), 102, 101, {"UP"}},

    // --- 邊界情況 (Boundary Cases) ---
    {"邊界: 起點終點相同", GetGeneralTree(), 4, 4, {}},
    {"邊界: 單節點樹, 起點終點相同", GetSingleNodeTree(), 200, 200, {}},
    {"邊界: 節點不存在 (start=99)", GetGeneralTree(), 99, 5, {}},
    {"邊界: 節點不存在 (end=99)", GetGeneralTree(), 1, 99, {}},

    // --- 空樹情況 (Boundary Case - Null Tree) ---
    {"邊界: 空樹", GetNullTree(), 1, 2, {}}};

void Test(ITreeWalk *pTreeWalk)
{
    for (const auto &testCase : testCases)
    {
        std::cout << "Running " << testCase.description << "...\n";
        pTreeWalk->SetBinaryTree(testCase.root);
        auto path = pTreeWalk->FindMinPath(testCase.start, testCase.end);
        if (path == testCase.expectedPath)
        {
            std::cout << "Test passed!\n";
        }
        else
        {
            std::cout << "Test failed!\n";
            std::cout << "Actual: ";
            for (const auto &direction : path)
                std::cout << direction << " ";
            std::cout << "\nExpected: ";
            for (const auto &direction : testCase.expectedPath)
                std::cout << direction << " ";
            std::cout << "\n\n";
        }
    }
}

int main(int argc, char **argv)
{
    std::vector<ITreeWalk *> walkers = {
        new SimpleTreeWalk(),
        new BinaryLiftingWalk(),
        new EulerRMQWalk(),
        new SimpleParentPointerWalk()};

    for (auto walker : walkers)
    {
        std::cout << "--- Algorithm: " << walker->GetAlgorithmName() << " ---" << std::endl;

        Test(walker);

        delete walker;
    }

    return 0;
}