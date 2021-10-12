#include "CommandParsing.h"

void Commands::CommandParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	std::string command = splitString(words, input)[0];
	int switchstatement = findCommandForSwitchStatement(command);

	switch (switchstatement) {
	case (1):
		editParsing(Table, input);
		break;
	case (2):
		addRowsOrColumns(Table, input);
		break;
	case (3):
		deleteRowsOrColumns(Table, input);
		break;
	case (4):
		insertParsing(Table, input);
		break;
	case (5):
		std::cout << "\nEXITING PROGRAM" << std::endl;
		break;
	case (6):
			saveParsing(Table, input);
		break;

	default:
		std::cout << "\nUnknown Command!" << std::endl;
		break;
	}

}
//	0		1		  2	 3
//save fileName.csv
//save fileName.csv -sep c
void Commands::saveParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	splitString(words, input);
	std::string sepCharFromArgToString = ";"; //words[3];

	if ((words.size() == 2) &&(sepCharFromArgToString.size() == 1)) { // save file with default separator
		std::cout << "Saving with default separator" << std::endl;
		std::string fileName = words[1];
		std::cout << fileName << std::endl;
		fileParsing::saveFile(Table, fileName, ";");
	}
	else if (((words.size() == 4) && (words[2] == "-sep")) && (words[3].size() == 1)) {
		std::cout << "Saving with custom separator" << std::endl;
		std::string fileName = words[1];
		std::cout << fileName << std::endl;
		sepCharFromArgToString = words[3];
		fileParsing::saveFile(Table, fileName, sepCharFromArgToString);
	}
	else
		std::cout << "Unknown Command" << std::endl;

}

int Commands::findCommandForSwitchStatement(std::string const& command) {
	std::map<std::string, int>::iterator it = command_codes.begin();

	while (it != command_codes.end()) {

		if (command == it->first)
			return it->second;
		it++;
	}

	return -1;
}

std::vector<std::string> Commands::splitString(std::vector<std::string> &words, std::string const& input) {
	char delimiter = ' ';
	int delimiterPos = 0;
	std::string remainingString = input;

	//tokenizes input between delimiters and pushes words to vector<string> words;
	while (remainingString.find(delimiter) != std::string::npos ){
		//std::cout << "Remaining string: " << remainingString << std::endl; // for debugging
		delimiterPos = 0;
		delimiterPos = remainingString.find(delimiter);
		if(remainingString.substr(0, delimiterPos) != "")
			words.push_back(remainingString.substr(0, delimiterPos));
		remainingString = remainingString.substr(delimiterPos + 1);
	}

	//If no more delimiter found, return push remaining string to vector
	if ((remainingString.find(delimiter) == std::string::npos) && (remainingString.size() != 0))
		words.push_back(remainingString);

	return words;
}

bool Commands::isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}
//	0	 1	2
// edit a111 asd

void Commands::editParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	splitString(words, input);
	if (words.size() >= 3){
		unsigned short int xPos = toupper(words[1][0]) - 'A' + 1;
		unsigned short int yPos = atoi(&words[1][1]);
		std::string toSet = input.substr(input.find(words[2],input.find(words[1]) + words[1].size()));

		Table->setCell(xPos, yPos, toSet);
	}
	else
		std::cout << "\nUnknown Command!" << std::endl;
}

// add N rows/cols
void Commands::addRowsOrColumns(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	splitString(words, input);

	int toAdd = atoi(&words[1][0]);
	bool isRow = (words[2] == "rows") ? true : false;
	bool isColumn = (words[2] == "columns") ? true : false;
	
	if (isRow) Table->addRows(toAdd);
	else if (isColumn) Table->addColumns(toAdd);
	else std::cout << "\nUnknown Command!\n";
}

// delete X/Y
void Commands::deleteRowsOrColumns(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	
	std::string toDelete = splitString(words, input)[1];

	if (isNumber(toDelete)) Table->deleteRow(atoi(&toDelete[0]));
	else if (isupper(toDelete[0])) Table->deleteColumn((toDelete[0] - 'A') + 1);
	else Table->deleteColumn((toDelete[0] - 'a') + 1);
}

// insert N rows/cols before/after X/Y
void Commands::insertParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	splitString(words, input);
	//std::vector::operator[] does not perform bounds checking, so it will NOT throw exception !!! -> leads to undefinde behavior

	if (((words[0] == "insert") && ((words[2] == "rows") || (words[2] == "columns"))) && ((words[3] == "before") || (words[3] == "after"))) {
		int toAdd = 0;
		int wheretoAdd = 0;
		try {
			toAdd = stoi(words[1]);
			if (isNumber(words[4])) wheretoAdd = stoi(words[4]);
			else wheretoAdd = toupper(words[4][0]) - 'A' + 1;
		}
		catch (std::invalid_argument& e) {
			std::cout << "\nInvalid parameters" << std::endl;
		}
		
		//Function Branching to Different types of insertions depending on wheter we insert a column/row and before/after we want to do it.
	
		//ROWS AFTER
		if ((words[2] == "rows") && (words[3] == "after"))
			Table->insertRowsAfter(toAdd, wheretoAdd);
		//ROWS BEFORE
		if ((words[2] == "rows") && (words[3] == "before"))
			Table->insertRowsBefore(toAdd, wheretoAdd);
		//COLUMNS AFTER
		if ((words[2] == "columns") && (words[3] == "after"))
			Table->insertColumnsAfter(toAdd, wheretoAdd);
		//COLUMNS BEFORE
		if ((words[2] == "columns") && (words[3] == "before"))
			Table->insertColumnsBefore(toAdd, wheretoAdd);
	}
	else
		std::cout << "\nInvalid input" << std::endl;

	//TRY to convert input N and X/Y data to string
	

}
