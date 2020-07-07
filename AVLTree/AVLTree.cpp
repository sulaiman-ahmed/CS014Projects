#include"AVLTree.h"
#include"Node.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
 
AVLTree::AVLTree() {
    root = nullptr;
}
 
void AVLTree::insert(const string &val) {
    if (root == 0) {
        root = new Node(val);
        return;
    }
   
    Node* valParent = search(val, root);
    Node* child = new Node(val);
    child->parent = valParent;
   
    if (val < valParent->data) {
        valParent->left = child;
    }
    else if (val > valParent->data) {
        valParent->right = child;
    }
    else {
        return;
    }
   
    Node* temp = findUnbalancedNode(child);
    if (temp) {
        rotate(temp);
    }
}

 
int AVLTree::balanceFactor(Node* node) {
    if (node == 0) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

void AVLTree::printBalanceFactors() {
    printBalanceFactors(root);
    cout << endl;
}
 
void AVLTree::visualizeTree(const string &outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tpng " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());      
}

//Private Helper Functions
Node* AVLTree::search(const string &val, Node* node) const {
    if (node->data == val) {
        return node;
    }
    if (val < node->data) {
        if (node->left) {
            return search(val, node->left);
        }
        else {
            return node;
        }
    }
    else {
        if (node->right) {
            return search(val, node->right);
        }
        return node;
    }
}

 
void AVLTree::printBalanceFactors(Node* node) {
    if(node) {
        printBalanceFactors(node->left);
        cout << node->data << "(" << balanceFactor(node) << "), ";
        printBalanceFactors(node->right);
    }
}
 
 
void AVLTree::visualizeTree(ofstream &outFS, Node *n) {
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS << n->data << " -> " << n->left->data <<";"<< endl;    
        }
 
        if(n->right){
            visualizeTree(outFS,n->right);
            outFS << n->data << " -> " << n->right->data <<";"<< endl;    
        }
    }
}
 
int AVLTree::height(Node* node) const {
    if (node == 0) {
        return -1;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    else {
        return rightHeight + 1;
    }
}
 
Node* AVLTree::findUnbalancedNode(Node* node) {
    if (node == 0) {
        return 0;
    }
   
    int bFactor = balanceFactor(node);
    if (bFactor == -2 || bFactor == 2) {
        return node;
    }
    else {
        return findUnbalancedNode(node->parent);
    }
}

Node* AVLTree::rotateRight(Node* node) {
    Node* leftRightChild = node->left->right;
    if(node->parent != NULL) {
        if(node->parent->left == node) {
            node->parent->left = node->left;
            if(node->left != NULL) {
                node->left->parent = node->parent;
            }
        }
        else if(node->parent->right == node) {
            node->parent->right = node->left;
            if(node->left != NULL) {
                node->left->parent = node->parent;
            }
        }
    }
    else {
        root = node->left;
        root->parent = NULL;
    }
    node->left->right = node;
    if(node != NULL) {
        node->parent = node->left;
    }
    node->left = leftRightChild;
    if(leftRightChild != NULL) {
        leftRightChild->parent = node;
    }
    return node->parent;
}
 
Node* AVLTree::rotateLeft(Node* node) {
    Node* rightLeftChild = node->right->left;
    if (node->parent != 0) {
        if (node->parent->right == node) {
            node->parent->right = node->right;
            if (node->right != 0) {
                node->right->parent = node->parent;
            }
        }
        else if (node->parent->left == node) {
            node->parent->left = node->right;
            if (node->right != 0) {
                node->right->parent = node->parent;
            }
        }
    }
    else {
        root = node->right;
        root->parent = 0;
    }
   
    node->right->left = node;
    if (node != 0) {
        node->parent = node->right;
    }
    node->right = rightLeftChild;
    if (rightLeftChild) {
        rightLeftChild->parent = node;
    }
    return node->parent;
}
 
void AVLTree::rotate(Node* node) {
    int bFactor = balanceFactor(node);
    int childBFactor1 = balanceFactor(node->left);
    int childBFactor2 = balanceFactor(node->right);
    if (bFactor == 2) {
        if (childBFactor1 == 1 || childBFactor2 == 1) {
            rotateRight(node);
        }
        else {
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    else {
        if (childBFactor1 == -1 || childBFactor2 == -1) {
            rotateLeft(node);
        }
        else {
            rotateRight(node->right);
            rotateLeft(node);
        }
    }
}