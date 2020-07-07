#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
#include <sstream>
#include <fstream>

#include "arithmeticExpression.h"

using namespace std;

arithmeticExpression::arithmeticExpression(const string& input) {
	infixExpression = input;
	root = nullptr;
}

void arithmeticExpression::buildTree() {
	string postFixExpression = infix_to_postfix();
	stack<TreeNode*> parentStack;
	for (unsigned i = 0; i < postFixExpression.size(); i++) {
		if (isalpha(postFixExpression.at(i))) {
			TreeNode* newNode = new TreeNode(postFixExpression.at(i), 'a' + i);
			parentStack.push(newNode);
		}
		else {
			TreeNode* firstNode = parentStack.top();
			parentStack.pop();
			TreeNode* secondNode = parentStack.top();
			parentStack.pop();
			TreeNode* newNode = new TreeNode(postFixExpression.at(i), 'a' + i);
			newNode->left = secondNode;
			newNode->right = firstNode;
			parentStack.push(newNode);
			if(i + 1 == postFixExpression.size()) {
				root = newNode;
			}
		}
	}
	
}

void arithmeticExpression::infix() {
	infix(root);
}

void arithmeticExpression::prefix() {
	prefix(root);
}

void arithmeticExpression::postfix() {
	postfix(root);
}

void arithmeticExpression::visualizeTree(const string & outputFilename) {
	ofstream outFS(outputFilename.c_str());
	if (!outFS.is_open()) {
		cout << "Error opening " << outputFilename << endl;
		return;
	}
	outFS << "digraph G {" << endl;
	visualizeTree(outFS, root);
	outFS << "}";
	outFS.close();
	string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
	string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
	system(command.c_str());
}

//Private helper functions
int arithmeticExpression::priority(char op) {
	int priority = 0;
	if (op == '(') {
		priority = 3;
	}
	else if (op == '*' || op == '/') {
		priority = 2;
	}
	else if (op == '+' || op == '-') {
		priority = 1;
	}
	return priority;
}

string arithmeticExpression::infix_to_postfix() {
	stack<char> s;
	ostringstream oss;
	char c;
	for (unsigned i = 0; i < infixExpression.size(); ++i) {
		c = infixExpression.at(i);
		if (c == ' ') {
			continue;
		}
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') { //c is an operator
			if (c == '(') {
				s.push(c);
			}
			else if (c == ')') {
				while (s.top() != '(') {
					oss << s.top();
					s.pop();
				}
				s.pop();
			}
			else {
				while (!s.empty() && priority(c) <= priority(s.top())) {
					if (s.top() == '(') {
						break;
					}
					oss << s.top();
					s.pop();
				}
				s.push(c);
			}
		}
		else {
			oss << c;
		}
	}
	while (!s.empty()) {
		oss << s.top();
		s.pop();
	}
	return oss.str();
}

void arithmeticExpression::infix(TreeNode * node) {
	if (node == nullptr) {
		return;
	}
	else {
		if(node->left != nullptr) {
			cout << "(";
		}
		infix(node->left);
		cout << node->data;
		infix(node->right);
		if(node->right != nullptr) {
			cout << ")";
		}
	}
}

void arithmeticExpression::prefix(TreeNode * node) {
	if (node == nullptr) {
		return;
	}
	else {
		cout << node->data;
		prefix(node->left);
		prefix(node->right);
	}
}

void arithmeticExpression::postfix(TreeNode * node) {
	if (node == nullptr) {
		return;
	}
	else {
		postfix(node->left);
		postfix(node->right);
		cout << node->data;
	}
}

void arithmeticExpression::visualizeTree(ofstream& outFS, TreeNode* curr) {
	if (curr) {
		outFS << curr->key << "[label=" << "\"" << curr->data << "\"" << "]" << endl;
		if (curr->left) {
			visualizeTree(outFS, curr->left);
			outFS << curr->key << "->" << curr->left->key << endl;
		}
		if (curr->right) {
			
			visualizeTree(outFS, curr->right);
			outFS << curr->key << "->" << curr->right->key << endl;
		}
		outFS << endl;
	}
}