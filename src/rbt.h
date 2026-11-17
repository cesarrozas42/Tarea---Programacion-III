#ifndef RBT_H
#define RBT_H

#include <iostream>

enum Color {
    RED,
    BLACK
};

struct RBNode {
    int key;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    explicit RBNode(int value);
};

class RedBlackTree {
private:
    RBNode* root;

    void rotateLeft(RBNode* node);
    void rotateRight(RBNode* node);
    void fixInsertion(RBNode* node);
    int calculateHeight(RBNode* node) const;
    int verifyProperties(RBNode* node, long long minValue,
                         long long maxValue) const;
    void preOrder(RBNode* node) const;
    void destroy(RBNode* node);

public:
    RedBlackTree();
    ~RedBlackTree();

    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator=(const RedBlackTree&) = delete;

    void insert(int key);
    bool verify() const;
    int height() const;
    void printPreOrder() const;
};

#endif
