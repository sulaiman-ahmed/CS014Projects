#ifndef Node_H
#define Node_H

#include <iostream>

using namespace std;

class Node {
    public:
        string data;
        Node* left;
        Node* right;
        Node* parent;
        int height;
        Node(string data);
        Node();
        
};

#endif