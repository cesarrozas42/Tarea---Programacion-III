#ifndef TAREA6_BST_H
#define TAREA6_BST_H

#include <stack>
#include <utility>
#include <vector>

#include "Node.h"

using namespace std;

class BST {
public:
    BST() : root_(nullptr), comparisons_(0) {}
    ~BST() { clear(); }

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    bool insert(int key) {
        Node* parent = nullptr;
        Node* cur = root_;
        while (cur != nullptr) {
            ++comparisons_;
            if (key == cur->key) return false;
            parent = cur;
            cur = (key < cur->key) ? cur->left : cur->right;
        }
        Node* node = new Node(key);
        if (parent == nullptr) {
            root_ = node;
        } else if (key < parent->key) {
            parent->left = node;
        } else {
            parent->right = node;
        }
        return true;
    }

    bool remove(int key) {
        Node* parent = nullptr;
        Node* cur = root_;
        while (cur != nullptr && cur->key != key) {
            parent = cur;
            cur = (key < cur->key) ? cur->left : cur->right;
        }
        if (cur == nullptr) return false;

        if (cur->left != nullptr && cur->right != nullptr) {
            Node* succParent = cur;
            Node* succ = cur->right;
            while (succ->left != nullptr) {
                succParent = succ;
                succ = succ->left;
            }
            cur->key = succ->key;
            parent = succParent;
            cur = succ;
        }

        Node* child = (cur->left != nullptr) ? cur->left : cur->right;
        if (parent == nullptr) {
            root_ = child;
        } else if (parent->left == cur) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete cur;
        return true;
    }

    bool contains(int key) const {
        Node* cur = root_;
        while (cur != nullptr) {
            if (key == cur->key) return true;
            cur = (key < cur->key) ? cur->left : cur->right;
        }
        return false;
    }

    vector<int> inorder() const {
        vector<int> out;
        stack<Node*> st;
        Node* cur = root_;
        while (cur != nullptr || !st.empty()) {
            while (cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top();
            st.pop();
            out.push_back(cur->key);
            cur = cur->right;
        }
        return out;
    }

    vector<int> preorder() const {
        vector<int> out;
        if (root_ == nullptr) return out;
        stack<Node*> st;
        st.push(root_);
        while (!st.empty()) {
            Node* cur = st.top();
            st.pop();
            out.push_back(cur->key);
            if (cur->right != nullptr) st.push(cur->right);
            if (cur->left != nullptr) st.push(cur->left);
        }
        return out;
    }

    int height() const {
        if (root_ == nullptr) return 0;
        int best = 0;
        stack<pair<Node*, int>> st;
        st.push({root_, 1});
        while (!st.empty()) {
            auto [node, level] = st.top();
            st.pop();
            if (level > best) best = level;
            if (node->left != nullptr) st.push({node->left, level + 1});
            if (node->right != nullptr) st.push({node->right, level + 1});
        }
        return best;
    }

    void clear() {
        stack<Node*> st;
        if (root_ != nullptr) st.push(root_);
        while (!st.empty()) {
            Node* cur = st.top();
            st.pop();
            if (cur->left != nullptr) st.push(cur->left);
            if (cur->right != nullptr) st.push(cur->right);
            delete cur;
        }
        root_ = nullptr;
        comparisons_ = 0;
    }

    Node* root() const { return root_; }

    long long comparisons() const { return comparisons_; }

private:
    Node* root_;
    long long comparisons_;
};

#endif
