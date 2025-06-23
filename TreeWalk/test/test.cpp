#include "TreeWalk.h"
#include <iostream>

auto setParent = [](Node *pParent, Node *pLeft, Node *pRight)
{
    if (pLeft)
        pLeft->m_pParent = pParent;
    if (pRight)
        pRight->m_pParent = pParent;
};

class Test1
{
public:
    Node *pNodeA = nullptr;
    Node *pNodeB = nullptr;
    Node *pNodeC = nullptr;
    Node *pNodeD = nullptr;
    Node *pNodeE = nullptr;
    Node *pNodeF = nullptr;
    Node *pNodeG = nullptr;

    Test1()
    {
        pNodeA = new Node('A');
        pNodeB = new Node('B');
        pNodeC = new Node('C');
        pNodeD = new Node('D');
        pNodeE = new Node('E');
        pNodeF = new Node('F');
        pNodeG = new Node('G');

        pNodeA->m_pLeft = pNodeB;
        pNodeA->m_pRight = pNodeC;
        pNodeB->m_pRight = pNodeD;
        pNodeC->m_pLeft = pNodeE;
        pNodeC->m_pRight = pNodeF;
        pNodeF->m_pLeft = pNodeG;
        setParent(pNodeA, pNodeB, pNodeC);
        setParent(pNodeB, nullptr, pNodeD);
        setParent(pNodeC, pNodeE, pNodeF);
        setParent(pNodeF, nullptr, pNodeG);
    }

    virtual ~Test1()
    {
        delete pNodeA;
        delete pNodeB;
        delete pNodeC;
        delete pNodeD;
        delete pNodeE;
        delete pNodeF;
        delete pNodeG;
    }

    void Run()
    {
        TreeWalk treeWalk;
        treeWalk.SetBinaryTree(pNodeA);

        // basic test from sample
        auto path1 = treeWalk.FindMinPath('B', 'F');
        std::vector<std::string> expectedPath1 = {"UP", "RIGHT", "RIGHT"};
        if (path1 != expectedPath1)
        {
            std::cout << "Test failed : Path from B to F\n";
            std::cout << "Actual: ";
            for (auto &direction : path1)
                std::cout << direction << " ";
            std::cout << "\nExpected: UP RIGHT RIGHT\n\n";
        }

        // Only UP
        auto path2 = treeWalk.FindMinPath('D', 'B');
        std::vector<std::string> expectedPath2 = {"UP"};
        if (path2 != expectedPath2)
        {
            std::cout << "Test failed: Path from D to B\n";
            std::cout << "Actual: ";
            for (auto &direction : path2)
                std::cout << direction << " ";
            std::cout << "\nExpected: UP\n\n";
        }

        // Only UP
        auto path3 = treeWalk.FindMinPath('E', 'A');
        std::vector<std::string> expectedPath3 = {"UP", "UP"};
        if (path3 != expectedPath3)
        {
            std::cout << "Test failed: Path from E to A\n";
            std::cout << "Actual: ";
            for (auto &direction : path3)
                std::cout << direction << " ";
            std::cout << "\nExpected: UP UP\n\n";
        }

        // Only LEFT
        auto path4 = treeWalk.FindMinPath('C', 'E');
        std::vector<std::string> expectedPath4 = {"LEFT"};
        if (path4 != expectedPath4)
        {
            std::cout << "Test failed: Path from C to E\n";
            std::cout << "Actual: ";
            for (auto &direction : path4)
                std::cout << direction << " ";
            std::cout << "\nExpected: LEFT\n\n";
        }

        // Only Right
        auto path5 = treeWalk.FindMinPath('A', 'F');
        std::vector<std::string> expectedPath5 = {"RIGHT", "RIGHT"};
        if (path5 != expectedPath5)
        {
            std::cout << "Test failed: Path from A to F\n";
            std::cout << "Actual: ";
            for (auto &direction : path5)
                std::cout << direction << " ";
            std::cout << "\nExpected: RIGHT RIGHT\n\n";
        }
    }
};

class Test2
{
public:
    Node *pNodeA = nullptr;
    Node *pNodeB = nullptr;
    Node *pNodeC = nullptr;
    Node *pNodeD = nullptr;
    Node *pNodeE = nullptr;
    Node *pNodeF = nullptr;

    Test2()
    {
        pNodeA = new Node('A');
        pNodeB = new Node('B');
        pNodeC = new Node('C');
        pNodeD = new Node('D');
        pNodeE = new Node('E');
        pNodeF = new Node('F');

        pNodeA->m_pLeft = pNodeB;
        pNodeA->m_pRight = pNodeC;
        pNodeB->m_pLeft = pNodeD;
        pNodeB->m_pRight = pNodeE;
        pNodeC->m_pRight = pNodeF;
        setParent(pNodeA, pNodeB, pNodeC);
        setParent(pNodeB, pNodeD, pNodeE);
        setParent(pNodeC, nullptr, pNodeF);

        Run();
    }

    ~Test2()
    {
        delete pNodeA;
        delete pNodeB;
        delete pNodeC;
        delete pNodeD;
        delete pNodeE;
        delete pNodeF;
    }

    void Run()
    {
        TreeWalk treeWalk;
        treeWalk.SetBinaryTree(pNodeA);

        auto path1 = treeWalk.FindMinPath('D', 'F');
        std::vector<std::string> expectedPath1 = {"UP", "UP", "RIGHT", "RIGHT"};
        if (path1 != expectedPath1)
        {
            std::cout << "Test failed: Path from D to F\n";
            std::cout << "Actual: ";
            for (auto &direction : path1)
                std::cout << direction << " ";
            std::cout << "\nExpected: UP UP RIGHT RIGHT\n\n";
        }

        auto path2 = treeWalk.FindMinPath('B', 'E');
        std::vector<std::string> expectedPath2 = {"RIGHT"};
        if (path2 != expectedPath2)
        {
            std::cout << "Test : Path from B to E\n";
            std::cout << "Actual: ";
            for (auto &direction : path2)
                std::cout << direction << " ";
            std::cout << "\nExpected: RIGHT\n\n";
        }

        auto path3 = treeWalk.FindMinPath('F', 'D');
        std::vector<std::string> expectedPath3 = {"UP", "UP", "LEFT", "LEFT"};
        if (path3 != expectedPath3)
        {
            std::cout << "Test failed: Path from F to D\n";
            std::cout << "Actual: ";
            for (auto &direction : path3)
                std::cout << direction << " ";
            std::cout << "\nExpected: UP UP LEFT LEFT\n\n";
        }

        auto path4 = treeWalk.FindMinPath('A', 'A');
        std::vector<std::string> expectedPath4 = {};
        if (path4 != expectedPath4)
        {
            std::cout << "Test failed: Path from A to A\n";
            std::cout << "Actual: ";
            for (auto &direction : path4)
                std::cout << direction << " ";
            std::cout << "\nExpected: (empty)\n\n";
        }

        auto path5 = treeWalk.FindMinPath('A', 'Z');
        std::vector<std::string> expectedPath5 = {};
        if (path5 != expectedPath5)
        {
            std::cout << "Test failed: Path from A to Z (non-existent)\n";
            std::cout << "Actual: ";
            for (auto &direction : path5)
                std::cout << direction << " ";
            std::cout << "\nExpected: (empty)\n\n";
        }
    }
};

void Test()
{
    std::cout << "Running Test1...\n";
    Test1 test1;
    test1.Run();

    std::cout << "Running Test2...\n";
    Test2 test2;
}