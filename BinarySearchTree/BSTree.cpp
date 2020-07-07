#include "BSTree.h"
#include <string>
#include <iostream>

using namespace std;

BSTree::BSTree() {
    root = nullptr;
}

BSTree::~BSTree() {
    delete root;
}

void BSTree::insert(const string &newString){
    insert(root, newString);
    return;
}

void BSTree::remove(const string &key){
    if(search(key)) {
        Node *curr = search(key, root);

        if(curr->count > 1) {
            curr->count = curr->count - 1;
        }
        else {
            remove(curr, key);
        }
    }
}

void BSTree::remove(Node *curr, const string& key) {
    if (!curr->left && !curr->right) {        
        if (!curr->parent) {// Node is root
            this->root = nullptr;
        } else if (curr->parent->left == curr) {
            curr->parent->left = nullptr;
        } else {
            curr->parent->right = nullptr;
        }
    } else if (curr->left && !curr->right) {    
        if (!curr->parent) { // Node is root
            this->root = curr->left;
        }
        else {
            Node *succ(nullptr);
            // Find successor (leftmost child of right subtree)
            succ = curr->left;
            while (succ->right) {
                succ = succ->right;
            }
            string successorData = succ->data;
            remove(succ->data);     
            curr->data = successorData;
        }

    } else if (!curr->left && curr->right) {    
        if (!curr->parent) {// Node is root
            this->root = curr->right;
        }
        else {
            Node *pred(nullptr);
            // Find successor (leftmost child of right subtree)
            pred = curr->right;
            while (pred->left) {
                pred = pred->left;
            }
            string predecessorData = pred->data;
            remove(pred->data);     
            curr->data = predecessorData;
        }

    } else {                                  
        Node *succ(nullptr);
        // Find successor (leftmost child of right subtree)
        succ = curr->left;
        while (succ->right) {
            succ = succ->right;
        }
        string successorData = succ->data;
        remove(succ->data);     
        curr->data = successorData;
    }
    return;
}

bool BSTree::search(const string &data) const { 
    return search(data, root);
}

Node * BSTree::search(const string &data, Node *curr) const { 
    if (curr != nullptr) {
        if (data == curr->data) {
            return curr;
        }
        else {
            if (data < curr->data) {
                if (curr->left) {
                    curr->left->parent = curr;
                }
                return search(data, curr->left);
            }
            else {
                if (curr->right) {
                    curr->right->parent = curr;
                }
                return search(data, curr->right);
            }
        }
    }
    else {
        return nullptr;
    }
}

string BSTree::largest() const{ 
    Node* curr = root;
    if(curr == nullptr) {
        return "";
    }
    else {
        while(1) {
            if(curr->right == 0) {
                return curr->data;
            }
            else {
                curr = curr->right;
            }
        }
    }
}

string BSTree::smallest() const{ 
    Node* curr = root;

    if(curr == nullptr) {
        return "";
    }
    else {
        while(1) {
            if(curr->left == 0) {
                return curr->data;
            }
            else {
                curr = curr->left;
            }
        }
    }
}

int BSTree::height(const string &data) const { 
    if (!search(data)) {
        return -1;
    }

    Node* curr = search(data, root);
    Node* currLeft = curr;
    Node* currRight = curr;
    int countLeft = 0;
    int countRight = 0;

    if (curr->left != nullptr) {
        currLeft = currLeft->left;
        countLeft++;
        countLeft = countLeft + height(currLeft->data);
    }

    if (curr->right != nullptr) {
        currRight = currRight->right;
        countRight++;
        countRight = countRight + height(currRight->data);
    }

    if (countLeft >= countRight) {
        return countLeft;
    }
    else {
        return countRight;
    }
}

void BSTree::preOrder() const { 
    preOrder(root);
    cout << endl;
}

void BSTree::postOrder() const {
    postOrder(root);
    cout << endl;
}

void BSTree::inOrder() const { 
    inOrder(root);
    cout << endl;
}

//PRIVATE
void BSTree::preOrder(Node* currNode) const {
    if (currNode) {
        cout << currNode->data << '(' << currNode->count << ')' << ", ";
        preOrder(currNode->left);
        preOrder(currNode->right);
    }
    return;
}

void BSTree::inOrder(Node* currNode) const {
    if (currNode) {
        inOrder(currNode->left);
        cout << currNode->data << '(' << currNode->count << ')' << ", ";
        inOrder(currNode->right);
    }
    return;
}

void BSTree::postOrder(Node* currNode) const {
    if (currNode) {
        postOrder(currNode->left);
        postOrder(currNode->right);
        cout << currNode->data << '(' << currNode->count << ')' << ", ";
    }
    return;
}

Node* BSTree::insert(Node* currNode, const string& newString) {
    Node* temp = nullptr;
    if (!root) {
        root = new Node(newString);
        return temp;
    }
    else if (!currNode) {
        return new Node(newString);
    }
    else if (newString == currNode->data) {
        ++currNode->count;
        return currNode;
    }
    else if (newString > currNode->data) {
        Node* rightChild = insert(currNode->right, newString);
        currNode->right = rightChild;
    }
    else {
        Node* leftChild = insert(currNode->left, newString);
        currNode->left = leftChild;
    }
    return currNode;
}