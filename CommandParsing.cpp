#include "CommandParsing.h"
Commands command_list;			//INSTANTIATION of Commands class for command codes

//INSERT N rows/cols before/after X/Y   function needs definition and declartion/implementation


void CommandParsing(myTable* Table, std::string const& input) {


	//Tokenize input string
	std::string command = InputTokenization(input);					//searching for existing command from input
	int switchstatement = findCommandForSwitchStatement(command);	//returning command Number from map command_codes


	switch (switchstatement) {
	case (1):
		editParsing(Table, input);
		break;
	case (3):
		deleteRowsOrColumns(Table, input);
		break;
	case (7):
		addRowsOrColumns(Table, input);
		break;
	case (5):
		std::cout << "EXITING PROGRAM" << std::endl;
		break;
	case (6):
		Table->addColumns(1);
		break;

	default:
		std::cout << "Unknown Command!" << std::endl;
		break;
	}



}


std::string InputTokenization(std::string const& input) {  // returns substring of input until first whitespace (delimiter)
	char delimiter = ' ';								   
	std::size_t found = input.find(delimiter);				

	return input.substr(0, found);
}

int findCommandForSwitchStatement(std::string const& command) {


	std::map<std::string, int>::iterator it = command_list.command_codes.begin();

	while (it != command_list.command_codes.end()) {

		if (command == it->first)
			return it->second;
		it++;
	}

	return -1; // For undefined command // switch default state
}

void editParsing(myTable* Table, std::string const& input) {  //Needs rewrite
	unsigned short int xPos = 0;
	unsigned short int yPos = 0;
	std::string toSet = "";
	xPos = int(tolower(input[5])) - 'a' + 1;  // Nagyon csunya stiiil ez az int cast megoldas
	yPos = int(input[6]) - 48;	// fuj
	toSet = input.substr(8);
	Table->setCell(xPos, yPos, toSet);

}

void addRowsOrColumns(myTable* Table, std::string const& input) {
	std::string temp = "";
	int toAdd = 0;

	if (input.find("rows") == 4) {				//ugly input checking code
		temp = input.substr(9);
		toAdd = stoi(temp);
		Table->addRows(toAdd);
	}

	if (input.find("columns") == 4) {			//ugly input checking code
		temp = input.substr(12);
		toAdd = stoi(temp);
		Table->addColumns(toAdd);
	}
}

void deleteRowsOrColumns(myTable* Table, std::string const& input) {  //delete x/y ... (ha betu, akkor oszlop, ha szam, akkor sor)
	std::string temp = "";											  // at kell irni betu/szam detektalasara, sokkal egyszerubb lesz, mint ez a szorny itt lejjebb				
	int toDelete = 0;

	if (input.find("row") == 7) {						//012345678901234..
		temp = input.substr(11);						//delete row x
		toDelete = stoi(temp);							
		Table->deleteRow(toDelete);

	}

	if (input.find("column") == 7) {					//012345678901234..
		temp = input.substr(14);						//delete column x
		toDelete = stoi(temp);
		Table->deleteColumn(toDelete);
	}
}
