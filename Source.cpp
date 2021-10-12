/* TODO LIST

- File mentése
	Save command
- Commands osztály funkcióit STATIKUSSÁ varázsolni

-MINDEN PARANCSRA LEHAL A PROGRAM, AHOL AZ NINCS VÉGIGÍRVA
	vector subscript out of range !!!  Vector element ellenôrzés a vector<words>-nek csak ott legyen, ahol létezik is az az elem !!!
	Mert a vector[] operatornál nincs bounds checking

 */

#include <iostream>
#include <string>

#include "myTable.h"
#include "CommandParsing.h"
#include "fileParsing.h"


//FORWARD DECLARATION
void userGuide(bool isWin);
void printTableOS(myTable* mtb, bool isWin);
void terminalRefresh(bool isWin);
void checkOS(bool &isWin);
myTable* checkArgCountForFileHandling(int argc, char** argv);


int main(int argc,  char **argv) {

	Commands commands;
	myTable* ptrToTable = nullptr;
	std::string input = "";

	ptrToTable = checkArgCountForFileHandling(argc, argv);

	bool isWin;
	checkOS(isWin);

	// Print User Guide
	userGuide(isWin);
	// Initial draw of Table
	printTableOS(ptrToTable, isWin);
	std::vector<std::string> vectorOfCommands;

	fileParsing::commandsFromFileToVector("input.txt", vectorOfCommands);

	for (int i = 0; i < vectorOfCommands.size();i++) {
		//terminalRefresh(isWin);						// refreshing terminal
		std::cout << vectorOfCommands[i] << std::endl;
		commands.CommandParsing(ptrToTable, vectorOfCommands[i]);	// UPDATE
		printTableOS(ptrToTable, isWin);
	}


	while (input != "exit" ) {	// MAIN LOOP - Basic "Game Loop"   Input -> Update -> Draw

		do {
		std::cout << ":"; getline(std::cin, input);	// INPUT
		} while (input == "");						// empty command
		terminalRefresh(isWin);						// refreshing terminal
		commands.CommandParsing(ptrToTable, input);	// UPDATE
		printTableOS(ptrToTable, isWin);			// DRAW
	}

	return 0;
}

//		0	   1	   2  3
//	./prog table.csv -sep ,

myTable* checkArgCountForFileHandling(int argc, char** argv) { // itt sok a sok a faszság meg a szétágazás
	myTable* ptrToTable = nullptr;

	if (argc == 2) {
		ptrToTable = fileParsing::fileHandling(argv); // create myTable from file
	}
	else if (argc == 4)
			ptrToTable = fileParsing::fileHandling(argv, argv[3]);	// create myTable from file with given separator character

	else {
		std::cout << "No or Wrong Arguments, creating default table" << std::endl;
		ptrToTable = new myTable;
	}

	if (ptrToTable == nullptr) {
		ptrToTable = new myTable;
	}

	return ptrToTable;
}

void userGuide(bool isWin) {
	if (!isWin) {
		std::cout << "┏━━━━━━━━━━━━━━User Guide━━━━━━━━━━━━━━━┓";
		std::cout << "\n┃edit XY string\t\t\t\t" << "┃";
		std::cout << "\n┃add N rows/cols\t\t\t" << "┃";
		std::cout << "\n┃delete X/Y\t\t\t\t" << "┃";
		std::cout << "\n┃insert N rows/cols before/after X/Y\t" << "┃";
		std::cout << "\n┃exit\t\t\t\t\t" << "┃";
		std::cout << "\n┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
	}
	else {
		std::cout << "+--------------User Guide---------------+";
		std::cout << "\n|edit XY string\t\t\t\t" << "|";
		std::cout << "\n|add N rows/cols\t\t\t" << "|";
		std::cout << "\n|delete X/Y\t\t\t\t" << "|";
		std::cout << "\n|insert N rows/cols before/after X/Y\t" << "|";
		std::cout << "\n|exit\t\t\t\t\t" << "|";
		std::cout << "\n+---------------------------------------+\n";
	}
}

void printTableOS(myTable* mtb, bool isWin) {
	if (!isWin)
		mtb->printTable();
	else
		mtb->printTableWin();
}

void terminalRefresh(bool isWin) {
	if (!isWin)
		std::system("clear");
	else
		std::system("cls");
}

void checkOS(bool& isWin) {
#ifdef __APPLE__ || __linux__
	isWin = false;
#elif _WIN32
	isWin = true;
#else
	std::cout << "Unidentified OS\n";
#endif
}