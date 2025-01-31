/*
Name: Aditya Gupta
Roll number : 102215265
group : 3NC4 / 3O1D
*/
#include <iostream>
using namespace std;

// Part 1: Insert an element (No duplicates allowed)
class TreeNode {
public:
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        key = value;
        left = right = nullptr;
    }
};

class BST {
private:
    TreeNode* root;

    // Insert function (Ensuring no duplicates)
    TreeNode* insert(TreeNode* node, int key) {
        if (node == nullptr) return new TreeNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        return node; // If key == node->key, we do nothing (no duplicates allowed)
    }
    
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    // Part 2: Delete an existing element
    TreeNode* deleteNode(TreeNode* node, int key) {
        if (node == nullptr) return node;
        if (key < node->key) node->left = deleteNode(node->left, key);
        else if (key > node->key) node->right = deleteNode(node->right, key);
        else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = findMin(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    // Part 3: Traversal methods
    void inOrder(TreeNode* node) {
        if (node) {
            inOrder(node->left);
            cout << node->key << " ";
            inOrder(node->right);
        }
    }

    void preOrder(TreeNode* node) {
        if (node) {
            cout << node->key << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(TreeNode* node) {
        if (node) {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->key << " ";
        }
    }

    // Part 4: Maximum and Minimum Depth of BST
    int maxDepth(TreeNode* node) {
        if (node == nullptr) return 0;
        return 1 + max(maxDepth(node->left), maxDepth(node->right));
    }

    int minDepth(TreeNode* node) {
        if (node == nullptr) return 0;
        if (!node->left) return 1 + minDepth(node->right);
        if (!node->right) return 1 + minDepth(node->left);
        return 1 + min(minDepth(node->left), minDepth(node->right));
    }

public:
    BST() { root = nullptr; }

    // Wrapper functions to call private methods
    void insert(int key) { root = insert(root, key); }
    void deleteKey(int key) { root = deleteNode(root, key); }
    
    void inOrderTraversal() { inOrder(root); cout << endl; }
    void preOrderTraversal() { preOrder(root); cout << endl; }
    void postOrderTraversal() { postOrder(root); cout << endl; }
    
    int getMaxDepth() { return maxDepth(root); }
    int getMinDepth() { return minDepth(root); }
};

// Driver Code
int main() {
    BST tree;
    
    // Insert elements into BST
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Traversals
    cout << "In-order Traversal: ";
    tree.inOrderTraversal();

    cout << "Pre-order Traversal: ";
    tree.preOrderTraversal();

    cout << "Post-order Traversal: ";
    tree.postOrderTraversal();

    // Max and Min Depth
    cout << "Max Depth: " << tree.getMaxDepth() << endl;
    cout << "Min Depth: " << tree.getMinDepth() << endl;

    // Delete a node and reprint In-order traversal
    tree.deleteKey(50);
    cout << "After deleting 50, In-order Traversal: ";
    tree.inOrderTraversal();

    return 0;
}