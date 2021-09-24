#include<iostream>
#include<string>

#include "myTable.h"
#include "CommandParsing.h"
using namespace std;


/*
	  ------- SOR / ROW----->  Cells[i].push_back(var);
	|					  Cells[i].resize(size, var);
	|
	|
  OSZLOP
  COLUMN        Cells.push_back(vector<int>());
	|		    Cells.resize(meret, vector<int>(0));
	|
	↓

*/

/*
standard bemeneten:
1   - oszlopok bovitese 1el
2   - sorok bovitese 1el
edit xy   - xy kordinátáju cella átváltása 1es értékre
exit	- kilép a program
*/
int main() {

	string input = "";
	myTable* ptrToTable = new myTable;


	while (input != "exit") { // MAIN LOOP

		ptrToTable->printTableSpecs();
		ptrToTable->printTable();
		cout << endl;
		getline(cin,input);
		CommandParsing(ptrToTable,input);
	}



	return 0;
}
