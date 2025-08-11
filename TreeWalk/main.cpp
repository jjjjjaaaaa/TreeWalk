#include "SimpleTreeWalk/SimpleTreeWalk.hpp"
#include "BinaryLiftingWalk/BinaryLiftingWalk.hpp"
#include "EulerRMQWalk/EulerRMQWalk.hpp"
#include "SimpleParentPointerWalk/SimpleParentPointerWalk.hpp"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <random>
#include <vector>

// --- 測試資料生成器 ---
Node *generateBalancedTree(int val_start, int depth)
{
    if (depth <= 0)
        return nullptr;
    Node *root = new Node(val_start);
    int children_base = val_start * 2;
    root->m_pLeft = generateBalancedTree(children_base, depth - 1);
    if (root->m_pLeft)
        root->m_pLeft->m_pParent = root;
    root->m_pRight = generateBalancedTree(children_base + 1, depth - 1);
    if (root->m_pRight)
        root->m_pRight->m_pParent = root;
    return root;
}

Node *generateStickTree(int num_nodes)
{
    if (num_nodes <= 0)
        return nullptr;
    Node *root = new Node(0);
    Node *curr = root;
    for (int i = 1; i < num_nodes; ++i)
    {
        curr->m_pLeft = new Node(i);
        curr->m_pLeft->m_pParent = curr;
        curr = curr->m_pLeft;
    }
    return root;
}

void FreeTree(Node *root)
{
    if (!root)
        return;
    FreeTree(root->m_pLeft);
    FreeTree(root->m_pRight);
    delete root;
}

std::pair<int, int> generateQuery(int num_nodes)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, num_nodes - 1);
    return {distrib(gen), distrib(gen)};
}

std::vector<ITreeWalk *> GetWalkers()
{
    return {
        new SimpleParentPointerWalk(),
        new SimpleTreeWalk(),
        new BinaryLiftingWalk(),
        new EulerRMQWalk(),
    };
}

const int TEST_COUNT = 10000;

// --- 測試場景執行器 ---

void runTestCase1()
{
    std::cout << "===== TestCase 1: 情境: 寬而淺的樹, 單次查詢 =====\n"
              << std::endl;

    std::map<std::string, double> mapAlgNameToPreProcessTime;
    std::map<std::string, double> mapAlgNameToQueryTime;
    std::map<std::string, double> mapAlgNameToClearTime;

    for (int i = 0; i < TEST_COUNT; i++)
    {
        Node *root = generateBalancedTree(1, 12);
        auto query = generateQuery(pow(2, 12) + 1);

        std::vector<ITreeWalk *> walkers = GetWalkers();

        for (auto walker : walkers)
        {
            auto start_pre = std::chrono::high_resolution_clock::now();
            walker->SetBinaryTree(root);
            auto end_pre = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> pre_time = end_pre - start_pre;
            if (pre_time.count() > 0)
                mapAlgNameToPreProcessTime[walker->GetAlgorithmName()] += pre_time.count();

            auto start_q = std::chrono::high_resolution_clock::now();
            walker->FindMinPath(query.first, query.second);
            auto end_q = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> q_time = end_q - start_q;
            if (q_time.count() > 0)
                mapAlgNameToQueryTime[walker->GetAlgorithmName()] += q_time.count();

            auto clear_start = std::chrono::high_resolution_clock::now();
            walker->Clear();
            auto clear_end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> clear_time = clear_end - clear_start;
            if (clear_time.count() > 0)
                mapAlgNameToClearTime[walker->GetAlgorithmName()] += clear_time.count();

            delete walker;
        }

        FreeTree(root);
    }

    for (const auto &entry : mapAlgNameToPreProcessTime)
    {
        std::cout << "Algorithm: " << entry.first << std::endl;

        std::cout << "Average Preprocessing Time for " << std::fixed << std::setprecision(4) << entry.second << " ms" << std::endl;
        std::cout << "Average Query Time for " << std::fixed << std::setprecision(4) << mapAlgNameToQueryTime[entry.first] << " ms" << std::endl;
        std::cout << "Average Clear Time for " << std::fixed << std::setprecision(4) << mapAlgNameToClearTime[entry.first] << " ms" << std::endl;

        std::cout << "Total Time for " << std::fixed << std::setprecision(4) << (entry.second + mapAlgNameToQueryTime[entry.first]) << " ms\n"
                  << std::endl;
    }
}

void runTestCase2()
{
    std::cout << "===== TestCase 2: 情境: 深長的竹竿樹 =====\n"
              << std::endl;

    int node_count = 2000;
    int query_count = 50000;

    std::map<std::string, double> mapAlgNameToPreProcessTime;
    std::map<std::string, double> mapAlgNameToQueryTime;
    std::map<std::string, double> mapAlgNameToClearTime;

    for (int i = 0; i < 10000; i++)
    {
        Node *root = generateStickTree(node_count);
        auto query = generateQuery(node_count + 2);

        std::vector<ITreeWalk *> walkers = GetWalkers();

        for (auto walker : walkers)
        {
            auto start_pre = std::chrono::high_resolution_clock::now();
            walker->SetBinaryTree(root);
            auto end_pre = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> pre_time = end_pre - start_pre;
            if (pre_time.count() > 0)
                mapAlgNameToPreProcessTime[walker->GetAlgorithmName()] += pre_time.count();

            auto start_q = std::chrono::high_resolution_clock::now();
            walker->FindMinPath(query.first, query.second);
            auto end_q = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> q_time = end_q - start_q;
            if (q_time.count() > 0)
                mapAlgNameToQueryTime[walker->GetAlgorithmName()] += q_time.count();

            auto clear_start = std::chrono::high_resolution_clock::now();
            walker->Clear();
            auto clear_end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> clear_time = clear_end - clear_start;
            if (clear_time.count() > 0)
                mapAlgNameToClearTime[walker->GetAlgorithmName()] += clear_time.count();

            delete walker;
        }

        FreeTree(root);
    }

    for (const auto &entry : mapAlgNameToPreProcessTime)
    {
        std::cout << "Algorithm: " << entry.first << std::endl;

        std::cout << "Average Preprocessing Time for " << std::fixed << std::setprecision(4) << entry.second << " ms" << std::endl;
        std::cout << "Average Query Time for " << std::fixed << std::setprecision(4) << mapAlgNameToQueryTime[entry.first] << " ms" << std::endl;
        std::cout << "Average Clear Time for " << std::fixed << std::setprecision(4) << mapAlgNameToClearTime[entry.first] << " ms" << std::endl;

        std::cout << "Total Time for " << std::fixed << std::setprecision(4) << (entry.second + mapAlgNameToQueryTime[entry.first]) << " ms\n"
                  << std::endl;
    }
}

int main(int argc, char **argv)
{
    runTestCase1();
    runTestCase2();
    return 0;
}
