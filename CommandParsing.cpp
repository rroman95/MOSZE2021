#include "CommandParsing.h"

void CommandParsing(myTable* Table, std::string const& input) {


	//Tokenize input string
	std::string command = InputTokenization(input);
	int switchstatement = findCommandForSwitchStatement(command);


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


std::string InputTokenization(std::string const& input) {
	char delimiter = ' ';
	std::size_t found = input.find(delimiter);

	return input.substr(0, found);
}

int findCommandForSwitchStatement(std::string const& command) {
	std::map<std::string, int> command_codes;
	command_codes.insert(std::pair<std::string, int>("edit", 1));
	command_codes.insert(std::pair<std::string, int>("addrow", 2));
	command_codes.insert(std::pair<std::string, int>("delete", 3));
	command_codes.insert(std::pair<std::string, int>("insert", 4));
	command_codes.insert(std::pair<std::string, int>("exit", 5));
	command_codes.insert(std::pair<std::string, int>("addcolumn", 6));
	command_codes.insert(std::pair<std::string, int>("add", 7));

	std::map<std::string, int>::iterator it = command_codes.begin();

	while (it != command_codes.end()) {

		if (command == it->first)
			return it->second;
		it++;
	}

	return -1; // For undefined command // switch default state
}

void editParsing(myTable* Table, std::string const& input) {
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

	if (input.find("rows") == 4) {						//NINCS teljes k�r� input ellen�rz�s !!!
		temp = input.substr(9);
		toAdd = stoi(temp);
		Table->addRows(toAdd);
	}

	if (input.find("columns") == 4) {						//NINCS teljes k�r� input ellen�rz�s !!!
		temp = input.substr(12);
		toAdd = stoi(temp);
		Table->addColumns(toAdd);
	}
}

void deleteRowsOrColumns(myTable* Table, std::string const& input) {
	std::string temp = "";
	int toDelete = 0;

	if (input.find("row") == 7) {						//NINCS teljes k�r� input ellen�rz�s !!!
		temp = input.substr(11);
		toDelete = stoi(temp);
		Table->deleteRow(toDelete);

	}

	if (input.find("column") == 7) {						//NINCS teljes k�r� input ellen�rz�s !!!
		temp = input.substr(14);
		toDelete = stoi(temp);
		Table->deleteColumn(toDelete);
	}
}