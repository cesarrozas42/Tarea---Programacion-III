#include "bfs.h"

#include <queue>
#include <utility>

bool isComplete(Node* root) {
    if (root == nullptr) {
        return true;
    }

    std::queue<Node*> q;
    q.push(root);
    bool foundMissingChild = false;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current->left != nullptr) {
            if (foundMissingChild) {
                return false;
            }
            q.push(current->left);
        } else {
            foundMissingChild = true;
        }

        if (current->right != nullptr) {
            if (foundMissingChild) {
                return false;
            }
            q.push(current->right);
        } else {
            foundMissingChild = true;
        }
    }

    return true;
}

int maxWidth(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    std::queue<Node*> q;
    q.push(root);
    int maximumWidth = 0;

    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());
        if (levelSize > maximumWidth) {
            maximumWidth = levelSize;
        }

        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

    return maximumWidth;
}

int minDepth(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    std::queue<std::pair<Node*, int>> q;
    q.push({root, 1});

    while (!q.empty()) {
        Node* current = q.front().first;
        int depth = q.front().second;
        q.pop();

        if (current->left == nullptr && current->right == nullptr) {
            return depth;
        }

        if (current->left != nullptr) {
            q.push({current->left, depth + 1});
        }
        if (current->right != nullptr) {
            q.push({current->right, depth + 1});
        }
    }

    return 0;
}
