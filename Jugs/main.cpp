#include "Jug.h" 
#include <iostream>
using namespace std;


void two() {
	string solution;
	Jug head(7, 11, 3, 1, 2, 3, 4, 5, 6);
	if (head.solve(solution) != 1) {
		cout << "Error 3" << endl;
	}
	cout << solution << endl << endl; 
}

void one() {
	string solution;
	Jug head( 3, 5, 4, 1, 1, 1, 1, 1, 2);         
	if(head.solve(solution) != 1) {
		cout << "Error 3" << endl;
	}
	cout << solution << endl;
}
	
int main() {
	two();
	one();
}