#include "Jug.h"
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <string>
using namespace std;


Jug::Jug(int a,int b,int c,int d,int e,int f,int g,int h,int i) {
	capA = a;
    capB = b;
    final = c;
    cFillA = d;
    cFillB = e;
    cEmptyA = f;
    cEmptyB = g;
    cPourAB = h;
    cPourBA = i;
    Node* fA = new Node("fill A");
    Node* fB = new Node("fill B");
    Node* eA = new Node("empty A");
    Node* eB = new Node("empty B");
    Node* pAB = new Node("pour A B");
    Node* pBA = new Node("pour B A");
    theAction.push_back(fA);
    theAction.push_back(fB);
    theAction.push_back(eA);
    theAction.push_back(eB);
    theAction.push_back(pAB);
    theAction.push_back(pBA);
    for (unsigned i = 0; i < theAction.size(); ++ i) {
    	for (unsigned j = 0; j < theAction.size(); ++j) {
    		if (!(i == j)) {
    			theAction.at(i)->neighbors.push_back(theAction.at(j));
    		}
    	}
    }
    
    pair<int,int> t;
    t.first = 0;
    t.second = 0;
    visitedPairs.push_back(t);
}


Jug::~Jug() {
	for (unsigned i = 0; i < theAction.size(); ++i) {
		delete theAction.at(i);
	}
}


int Jug::solve(string &solution) {
	solution = ""; 
	if (cFillA < 0 || cFillB < 0 || cEmptyA < 0 || cEmptyB < 0 || cPourAB < 0 || cPourBA < 0) {
		return -1;
	}
	if (!(0 < capA && capA <= capB)) {
		return -1;
	}
	if (!(final <= capB && capB <= 1000)) {
		return -1;
	}
	const string& temp = solution;
	solution = solve(temp);
	if (solution == "") {
		return 0;
	}
	return 1;
}


string Jug::solve(const string &solution) {
	queue<Paths> q;
	Paths temp1;
	Paths temp2;
	pair<int,int> emptyPair;
	emptyPair.first = 0;
    emptyPair.second = 0;
	temp1 = doAction(emptyPair, theAction.at(0));
	temp2 = doAction(emptyPair, theAction.at(1));
	visitedPairs.push_back(temp1.curPair);
	visitedPairs.push_back(temp2.curPair);
	q.push(temp1);
	q.push(temp2);
	Paths curNode;
	Paths tempPath;
	while (!q.empty()) {
		curNode = q.front();
		for(unsigned i = 0; i < curNode.n->neighbors.size(); ++i) {
			tempPath = doAction(curNode.curPair, curNode.n->neighbors.at(i));
			if (tempPath.curPair.second == final) {
				tempPath.cost += curNode.cost;
				tempPath.str = curNode.str + "\n" + tempPath.str;
				if (tempPath.curPair.first != 0) {
					tempPath.cost += cEmptyA;
					tempPath.str += "\nempty A";
				}
				tempPath.str = tempPath.str + "\nsuccess " + to_string(tempPath.cost);
				v.push_back(tempPath);
			} else if (!prevVisited(tempPath.curPair)) {
				visitedPairs.push_back(tempPath.curPair);
				tempPath.str = curNode.str + "\n" + tempPath.str;
				tempPath.cost += curNode.cost;
				q.push(tempPath);
			}
		}
		q.pop();
	}
	if (v.size() != 0) {
		int small = 100000;
		int indexsmall = 0;
		for (unsigned i = 0; i < v.size(); ++i) {
			if (v.at(i).cost < small) {
				small = v.at(i).cost;
				indexsmall = i;
			}
		}
		return v.at(indexsmall).str;
	}
	return "";
}

bool Jug::prevVisited(const pair<int,int> &p) {
	for (unsigned i = 0; i < visitedPairs.size(); ++i) {
		if (p == visitedPairs.at(i)) {
			return true;
		}
	}
	return false;
}

Paths Jug::doAction(const pair<int,int> &p, Node* n1) {
	Paths temp;
	
    temp.n = n1;
    
	if (n1->action == "fill A") {
        temp.curPair = fillA(p);
        temp.cost = cFillA;
        temp.str = "fill A";
        return temp;
    } 
    
    if (n1->action == "fill B") {
    	temp.curPair = fillB(p);
    	temp.cost = cFillB;
    	temp.str = "fill B";
    	return temp;
    }
    
    if (n1->action == "empty A") {
    	temp.curPair = emptyA(p);
    	temp.cost = cEmptyA;
    	temp.str = "empty A";
    	return temp;
    }
    
    if (n1->action == "empty B") {
    	temp.curPair = emptyB(p);
    	temp.cost = cEmptyB;
    	temp.str = "empty B";
    	return temp;
    } 
    
    if (n1->action == "pour A B") {
    	temp.curPair = pourAB(p);
    	temp.cost = cPourAB;
    	temp.str = "pour A B";
    	return temp;
    }
    
    temp.curPair = pourBA(p);
    temp.cost = cPourBA;
    temp.str = "pour B A";
    
    return temp;
}

pair<int,int> Jug::makePair(int n, int m) {
	pair<int,int> temp;
	
	temp.first = n;
	temp.second = m;
	
	return temp;
}

pair<int,int> Jug::fillA(const pair<int,int> &p) {
	pair<int,int> temp = p;
	
	temp.first = capA;
	
	return temp;
}

pair<int,int> Jug::fillB(const pair<int,int> &p) {
	pair<int,int> temp = p;
	
	temp.second = capB;
	
	return temp;
}

pair<int,int> Jug::emptyA(const pair<int,int> &p) {
	pair<int,int> temp = p;
	
	temp.first = 0;
	
	return temp;
}

pair<int,int> Jug::emptyB(const pair<int,int> &p) {
	pair<int,int> temp = p;
	
	temp.second = 0;
	
	return temp;
}

pair<int,int> Jug::pourAB(const pair<int,int> &p) {
	pair<int,int> temp;
	if (p.second + p.first < capB) {
		temp.first = 0;
		temp.second = p.first + p.second;
	} 
	
	else {
		temp.first = (p.first + p.second) - capB;
		temp.second = capB;
	}
	return temp;
}

pair<int,int> Jug::pourBA(const pair<int,int> &p) {
	pair<int,int> temp;
	if (p.second + p.first < capA) {
		temp.first = p.first + p.second;
		temp.second = 0;
	}
	else {
		temp.first = capA;
		temp.second = (p.first + p.second) - capA;
	}
	
	return temp;
}