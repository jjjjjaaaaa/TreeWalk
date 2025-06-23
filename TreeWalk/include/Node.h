#pragma once

typedef struct Node{
    char m_val;
    Node* m_pLeft = nullptr;
    Node* m_pRight = nullptr;
    Node* m_pParent = nullptr;

    Node(char val) : m_val(val) {}
} Node;

constexpr char STRING_UP[] = "UP";
constexpr char STRING_LEFT[] = "LEFT";
constexpr char STRING_RIGHT[] = "RIGHT";
