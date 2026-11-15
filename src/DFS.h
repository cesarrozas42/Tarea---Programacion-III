#ifndef TAREA6_DFS_H
#define TAREA6_DFS_H

#include <stack>
#include <vector>

#include "Node.h"

using namespace std;

inline bool findPathWithSum(Node* root, int K, vector<int>& path) {
    path.clear();
    if (root == nullptr) return false;

    struct Frame {
        Node* node;
        long long sum;
        size_t depth;
    };

    stack<Frame> st;
    st.push({root, root->key, 0});

    while (!st.empty()) {
        Frame f = st.top();
        st.pop();

        path.resize(f.depth);
        path.push_back(f.node->key);

        bool isLeaf = (f.node->left == nullptr && f.node->right == nullptr);
        if (isLeaf) {
            if (f.sum == K) return true;
            continue;
        }

        if (f.node->right != nullptr)
            st.push({f.node->right, f.sum + f.node->right->key, f.depth + 1});
        if (f.node->left != nullptr)
            st.push({f.node->left, f.sum + f.node->left->key, f.depth + 1});
    }

    path.clear();
    return false;
}

#endif
