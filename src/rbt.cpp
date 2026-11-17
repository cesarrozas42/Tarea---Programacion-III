#include "rbt.h"

RBNode::RBNode(int value)
    : key(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {
}

RedBlackTree::RedBlackTree() : root(nullptr) {
}

RedBlackTree::~RedBlackTree() {
    destroy(root);
}

void RedBlackTree::destroy(RBNode* node) {
    if (node == nullptr) {
        return;
    }

    destroy(node->left);
    destroy(node->right);
    delete node;
}

void RedBlackTree::rotateLeft(RBNode* node) {
    RBNode* rightChild = node->right;

    node->right = rightChild->left;
    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::rotateRight(RBNode* node) {
    RBNode* leftChild = node->left;

    node->left = leftChild->right;
    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->right) {
        node->parent->right = leftChild;
    } else {
        node->parent->left = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

void RedBlackTree::insert(int key) {
    RBNode* newNode = new RBNode(key);
    RBNode* parent = nullptr;
    RBNode* current = root;

    while (current != nullptr) {
        parent = current;

        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            delete newNode;
            return;
        }
    }

    newNode->parent = parent;

    if (parent == nullptr) {
        root = newNode;
    } else if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    fixInsertion(newNode);
}

void RedBlackTree::fixInsertion(RBNode* node) {
    while (node != root && node->parent->color == RED) {
        RBNode* parent = node->parent;
        RBNode* grandparent = parent->parent;

        if (parent == grandparent->left) {
            RBNode* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    node = parent;
                    rotateLeft(node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRight(node->parent->parent);
            }
        } else {
            RBNode* uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    rotateRight(node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(node->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

int RedBlackTree::calculateHeight(RBNode* node) const {
    if (node == nullptr) {
        return -1;
    }

    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int RedBlackTree::height() const {
    return calculateHeight(root);
}

int RedBlackTree::verifyProperties(RBNode* node, long long minValue,
                                   long long maxValue) const {
    if (node == nullptr) {
        return 1;
    }

    if (node->key <= minValue || node->key >= maxValue) {
        return -1;
    }

    if (node->color != RED && node->color != BLACK) {
        return -1;
    }

    if (node->color == RED) {
        if ((node->left != nullptr && node->left->color == RED) ||
            (node->right != nullptr && node->right->color == RED)) {
            return -1;
        }
    }

    if (node->left != nullptr && node->left->parent != node) {
        return -1;
    }

    if (node->right != nullptr && node->right->parent != node) {
        return -1;
    }

    int leftBlackHeight =
        verifyProperties(node->left, minValue, node->key);
    int rightBlackHeight =
        verifyProperties(node->right, node->key, maxValue);

    if (leftBlackHeight == -1 || rightBlackHeight == -1 ||
        leftBlackHeight != rightBlackHeight) {
        return -1;
    }

    return leftBlackHeight + (node->color == BLACK ? 1 : 0);
}

bool RedBlackTree::verify() const {
    if (root == nullptr) {
        return true;
    }

    if (root->color != BLACK || root->parent != nullptr) {
        return false;
    }

    return verifyProperties(root, LLONG_MIN, LLONG_MAX) != -1;
}

void RedBlackTree::preOrder(RBNode* node) const {
    if (node == nullptr) {
        return;
    }

    std::cout << node->key
              << '(' << (node->color == RED ? "R" : "B") << ") ";

    preOrder(node->left);
    preOrder(node->right);
}

void RedBlackTree::printPreOrder() const {
    preOrder(root);
    std::cout << '\n';
}
