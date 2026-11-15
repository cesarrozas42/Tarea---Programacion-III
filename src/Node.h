#ifndef TAREA6_NODE_H
#define TAREA6_NODE_H

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    explicit Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

#endif
