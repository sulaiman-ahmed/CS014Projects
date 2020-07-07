#include "Node.h"

#include <iostream>
#include <string>

using namespace std;

Node :: Node(string data){
    this->data = data;
    count = 1;
    left = 0;
    right = 0;
    parent = 0;
}
