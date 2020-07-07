#include "Node.h"

Node::Node(string data) {
    this->data = data;
    left = nullptr;
    right = nullptr;
    height = 0;
    parent = nullptr;
}

Node::Node() {
    data = "";
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 0;
}

