#include <iostream>
#include <string>

#include "myTable.h"
#include "Cell.h"

#include "CommandParsing.h"
#include "fileParsing.h"

//FORWARD DECLARATION
void userGuide(bool isWin);
void printTableOS(myTable* mtb, bool isWin);
void terminalRefresh(bool isWin);
void checkOS(bool &isWin);
myTable* checkArgCountForFileHandling(int argc, char** argv);
 

//MAIN
int main(int argc,  char **argv) {
	Commands commands;
	myTable* ptrToTable = nullptr;
	std::string input = "";

	ptrToTable = checkArgCountForFileHandling(argc, argv);

	bool isWin;
	checkOS(isWin);

	userGuide(isWin); // Print User Guide
	std::cout << "DEBUG LINE\n";
	ptrToTable->promoteCellsAfterFileParsing(ptrToTable);
	
	printTableOS(ptrToTable, isWin); // Initial draw of Table
	

	while (input != "exit") {	// MAIN LOOP - Basic "Game Loop"   Input -> Update -> Draw

		do {
		std::cout << ":"; getline(std::cin, input);	// INPUT
		} while (input == "");						// empty command
		terminalRefresh(isWin);						// refreshing terminal
		userGuide(isWin);							// user guide
		commands.CommandParsing(ptrToTable, input);	// UPDATE
		printTableOS(ptrToTable, isWin);			// DRAW
		

	}

	delete ptrToTable;

	return 0;
}

/** Checks, wheter there is a file as argument, if no starts the main loop with a default table */
myTable* checkArgCountForFileHandling(int argc, char** argv) {
	myTable* ptrToTable = nullptr;

	if (argc == 2) {
		ptrToTable = fileParsing::fileHandling(argv); // create myTable from file
	}
	else if (argc == 4)
			ptrToTable = fileParsing::fileHandling(argv, argv[3]); // create myTable from file with given separator character

	else {
		std::cout << "No or Wrong Arguments, creating default table" << std::endl;
		ptrToTable = new myTable("def_table");
	}

	if (ptrToTable == nullptr) {
		ptrToTable = new myTable("def_table");
	}

	return ptrToTable;
}

/** LINUX AND iOS type User Guide */
void userGuide(bool isWin) {
	if (!isWin) {
		std::cout << "┏━━━━━━━━━━━━━━User Guide━━━━━━━━━━━━━━━┓";
		std::cout << "\n┃edit XY string\t\t\t\t" << "┃";
		std::cout << "\n┃add N rows/columns\t\t\t" << "┃";
		std::cout << "\n┃delete X/Y\t\t\t\t" << "┃";
		std::cout << "\n┃insert N rows/cols before/after X/Y\t" << "┃";
		std::cout << "\n┃save filename.csv [-sep ,]\t\t" << "┃";
		std::cout << "\n┃sort by X/Y [asc/desc (default: asc)]\t" << "┃";
		std::cout << "\n┃swap MN XY\t\t\t\t" << "┃";
		std::cout << "\n┃align XY left/right\t\t\t" << "┃";
		std::cout << "\n┃align MN:XY left/right\t\t\t" << "┃";
		std::cout << "\n┃clear MN:XY\t\t\t\t" << "┃";
		std::cout << "\n┃exit\t\t\t\t\t" << "┃";
		std::cout << "\n┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
	}
	else {
		std::cout << "+--------------User Guide---------------+";
		std::cout << "\n|edit XY string\t\t\t\t" << "|";
		std::cout << "\n|add N rows/columns\t\t\t" << "|";
		std::cout << "\n|delete X/Y\t\t\t\t" << "|";
		std::cout << "\n|insert N rows/cols before/after X/Y\t" << "|";
		std::cout << "\n|save filename.csv [-sep ,]\t\t" << "|";
		std::cout << "\n|sort by X/Y [asc/desc (default: asc)]\t" << "|";
		std::cout << "\n|swap MN XY\t\t\t\t" << "|";
		std::cout << "\n|align XY left/right\t\t\t" << "|";
		std::cout << "\n|align MN:XY left/right\t\t\t" << "|";
		std::cout << "\n|clear MN:XY\t\t\t\t" << "|";
		std::cout << "\n|exit\t\t\t\t\t" << "|";
		std::cout << "\n+---------------------------------------+\n";
	}
}

/** Prints the Table depending on the host OS */
void printTableOS(myTable* mtb, bool isWin) {
	if (!isWin)
		mtb->printTable();
	else
		mtb->printTableWin();
}

/** Clears the terminal depending on the host OS */
void terminalRefresh(bool isWin) {
	if (!isWin)
		std::system("clear");
	else
		std::system("cls");
}

/** host OS check */
void checkOS(bool& isWin) {
#ifdef __APPLE__
	isWin = false;
#elif __linux__
	isWin = false;
#elif _WIN32
	isWin = true;
#else
	std::cout << "Unidentified OS\n";
#endif
}
