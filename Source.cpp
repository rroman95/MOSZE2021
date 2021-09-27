// GIT BRANCH TESTING
#include<iostream>
#include<string>

#include "myTable.h"
#include "CommandParsing.h"

using namespace std;

/*
standard bemeneten:
edit [char][num] string...
add rows [num]
add columns [num]
remove row [num]
remove column [num] 
exit	- kilép a program
*/

int main() {

	string input = "";
	myTable* ptrToTable = new myTable;

	ptrToTable->printTableSpecs();
	ptrToTable->printTable();					//Initial draw of Table

	while (input != "exit") { // MAIN LOOP - Basic "Game Loop"   Input -> Update -> Draw

		cout << ":"; getline(cin, input);		// INPUT
		CommandParsing(ptrToTable, input);		// UPDATE
		ptrToTable->printTableSpecs();			// for debugging - printing table dimensions
		ptrToTable->printTable();				// DRAW
	}



	return 0;
}
