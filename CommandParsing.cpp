#include "CommandParsing.h"

void Commands::CommandParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	std::string command = splitString(words, input)[0];
	int switchstatement = findCommandForSwitchStatement(command);
	std::cout << switchstatement << std::endl;

	switch (switchstatement) {
	case 1:
		editParsing(Table, input);
		break;
	case 2:
		addRowsOrColumns(Table, input);
		break;
	case 3:
		deleteRowsOrColumns(Table, input);
		break;
	case 4:
		insertParsing(Table, input);
		break;
	case 5:
		std::cout << "\nEXITING PROGRAM" << std::endl;
		break;
	case 6:
		saveParsing(Table, input);
		break;
	case 7:
		alignParsing(Table, input);
		break;
	case 8:
		swapParsing(Table, input);
		break;
	case 9:
		sortParsing(Table, input);
		break;
	case 10:
		clearParsing(Table, input);
		break;
	case 11:
		setParsing(Table, input);
		break;

	default:
		std::cout << "\nCommand not found int MAP!" << std::endl;
		break;
	}

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
	std::string validNum = "[0-9]*[.]?[0-9]";
	
	if (str == ".")
		return false;
	else if (std::regex_match(str, std::regex(validNum)))
		return true;
	else
		return false;
	/*if (str == "") return false;
    for (char const &c : str) {
		if (c == '.') continue;
        else if (!std::isdigit(c)) return false;
    }
    return true;*/
}

bool Commands::isValidRangeFormat(const std::string& str) {
	std::string validReg = "[a-zA-Z][0-9]+:[a-zA-Z][0-9]+";

	if (std::regex_match(str, std::regex(validReg))) {
		return true;
	} else {
		return false;
	}
}

std::pair<std::string, std::string> Commands::getRangeCornerStrings(const std::string& range) {
	return {range.substr(0, range.find(":")), range.substr(range.find(":")+1)};
}

std::tuple<int, int, int, int> Commands::getRangeCornerInts(const std::string& range) {
	int topLeftLetter;
	int bottomRightLetter;
	int topLeftNumber;
	int bottomRightNumber;

	if (getRangeCornerStrings(range).first[0] < getRangeCornerStrings(range).second[0]) {
		topLeftLetter = (toupper(getRangeCornerStrings(range).first[0]) - 'A');
		bottomRightLetter = (toupper(getRangeCornerStrings(range).second[0]) - 'A');
	} else {
		bottomRightLetter = (toupper(getRangeCornerStrings(range).first[0]) - 'A');
		topLeftLetter = (toupper(getRangeCornerStrings(range).second[0]) - 'A');
	}
	if (std::stoi(getRangeCornerStrings(range).first.substr(1)) < std::stoi(getRangeCornerStrings(range).second.substr(1))) {
		topLeftNumber = std::stoi(getRangeCornerStrings(range).first.substr(1)) - 1;
		bottomRightNumber = std::stoi(getRangeCornerStrings(range).second.substr(1)) - 1;
	} else {
		bottomRightNumber = std::stoi(getRangeCornerStrings(range).first.substr(1)) - 1;
		topLeftNumber = std::stoi(getRangeCornerStrings(range).second.substr(1)) - 1;
	}

	return std::make_tuple(topLeftLetter, bottomRightLetter, topLeftNumber, bottomRightNumber);
}

void Commands::editParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	splitString(words, input);
	unsigned short int xPos = toupper(words[1][0]) - 'A' + 1;
	unsigned short int yPos = atoi(&words[1][1]);
	if (Table->checkBounds(xPos, yPos)) {

	

		//edit a1 =SUM
		//Check if input creates an Aggregate Function
		if ((words[2][0] == '=') && (Aggregate_Cell::findAggregateFunctionType(words[2].substr(1, 3)) != -1)) {
			std::cout << "Input creates aggregate cell\n";
			std::cout << "words[2].substr " << words[2].substr(1, 4);
			int functionType = Aggregate_Cell::findAggregateFunctionType(words[2].substr(1, 3));
			std::string AggregateString = words[2];
			Table->promoteCellToAggregate(Table, yPos, xPos, functionType, AggregateString);

		}
		//Using default Cell
		else {

			std::cout << "default cell\n";
			if (words.size() >= 3) {
				std::string toSet = input.substr(input.find(words[2], input.find(words[1]) + words[1].size()));

				//Check if Cell is Aggregate, if yes denote it to basic Cell
				if (dynamic_cast<Aggregate_Cell*>(Table->getCellObject(xPos - 1, yPos - 1))) {
					std::cout << "Cell is Aggregate\n";
					Table->demoteAggregateToCell(yPos, xPos, toSet);
					std::cout << "demoting\n";
				}
				else {
					std::cout << "Cell is basic\n";
					Table->setCell(xPos, yPos, toSet);
				}
			}
			else
				std::cout << "\nUnknown Command!" << std::endl;
		}
	}
}

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

void Commands::deleteRowsOrColumns(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	
	std::string toDelete = splitString(words, input)[1];

	if (isNumber(toDelete)) Table->deleteRow(atoi(&toDelete[0]));
	else if (isupper(toDelete[0])) Table->deleteColumn((toDelete[0] - 'A') + 1);
	else Table->deleteColumn((toDelete[0] - 'a') + 1);
}

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
			(void)e;
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

void Commands::saveParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	splitString(words, input);
	std::string sepCharFromArgToString = ";"; //words[3];

	if ((words.size() == 2) &&(sepCharFromArgToString.size() == 1)) { // save file with default separator
		std::cout << "Saving with default separator" << std::endl;
		std::string fileName = words[1];
		fileParsing::saveFile(Table, fileName, ";");
	}
	else if (((words.size() == 4) && (words[2] == "-sep")) && (words[3].size() == 1)) {
		std::cout << "Saving with custom separator: " << words[3] << std::endl;
		std::string fileName = words[1];
		std::cout << fileName << std::endl;
		sepCharFromArgToString = words[3];
		fileParsing::saveFile(Table, fileName, sepCharFromArgToString);
	}
	else
		std::cout << "Unknown Command" << std::endl;

}

void Commands::alignParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	splitString(words, input);

	std::string range = splitString(words, input)[1];

	if ((words.size() >= 3) && ((words[2] == "left") || (words[2] == "right"))){
		if (isValidRangeFormat(range)) {
			const auto& [topLeftLetter, bottomRightLetter, topLeftNumber, bottomRightNumber] = getRangeCornerInts(range);

			char toSet = input.substr(input.find(words[2],input.find(words[1]) + words[1].size()))[0];
			
			if ((Table->cellExists(topLeftLetter, topLeftNumber)) && Table->cellExists(bottomRightLetter, bottomRightNumber)) {
				for (int i = topLeftNumber; i < bottomRightNumber+1; i++) {
					for (int j = topLeftLetter; j < bottomRightLetter+1; j++) {
						Table->setCellAlignment(i, j, toSet);
					}
				}
			}
		}
		else {unsigned short int xPos = toupper(words[1][0]) - 'A';
		unsigned short int yPos = atoi(&words[1][1]) - 1;
		char toSet = input.substr(input.find(words[2],input.find(words[1]) + words[1].size()))[0];

		Table->setCellAlignment(xPos, yPos, toSet);}
	}
	else
		std::cout << "\nUnknown Command!" << std::endl;
}

void Commands::swapParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	splitString(words, input);

	if (words.size() >= 3) {
		//Get CELL_A pos
		unsigned short int yPos_A = toupper(words[1][0]) - 'A';
		unsigned short int xPos_A = atoi(&words[1][1]) - 1;
		//Get CELL_B pos
		unsigned short int yPos_B = toupper(words[2][0]) - 'A';
		unsigned short int xPos_B = atoi(&words[2][1]) - 1;
		
		if ((Table->cellExists(yPos_A, xPos_A)) && (Table->cellExists(yPos_B, xPos_B))) {
			std::cout << "Swapping elements\n";
			Table->swapElements(yPos_A, xPos_A, yPos_B, xPos_B);

		}
		else { std::cout << "Cell doesnt exists\n"; }



		Table->checkColumnsMaxLength();
	}
	else
		std::cout << "\nUnknown Command!" << std::endl;
}

void Commands::sortParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	splitString(words, input);

	bool isAsc = true;
	if (words.size() == 3) 
		isAsc = true;
	else {
		if (words[3] == "asc") isAsc = true;
		else if (words[3] == "desc") isAsc = false;
		else std::cout << "\nUnknown Command!" << std::endl;
	}

	if (isNumber(words[2])) Table->sortRow((atoi(&words[2][0]))-1, isAsc);
	else if (isupper(words[2][0])) Table->sortColumn((words[2][0] - 'A'), isAsc);
	else Table->sortColumn((words[2][0] - 'a'), isAsc);
}

void Commands::clearParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;

	std::string range = splitString(words, input)[1];

	if (isValidRangeFormat(range)) {
		
		const auto& [topLeftLetter, bottomRightLetter, topLeftNumber, bottomRightNumber] =
		getRangeCornerInts(range);

		if ((Table->cellExists(topLeftLetter, topLeftNumber)) && Table->cellExists(bottomRightLetter, bottomRightNumber)) {
			for (int i = topLeftNumber; i < bottomRightNumber+1; i++) {
				for (int j = topLeftLetter; j < bottomRightLetter+1; j++) {
					Table->resetCell(i, j);
				}
			}
		} else {
			std::cout << "\nInvalid range\n";
		}

		}

	}

void Commands::setParsing(myTable* Table, std::string const& input) {
	std::vector<std::string> words;
	splitString(words, input);
	unsigned short int xPos = toupper(words[1][0]) - 'A' + 1;
	unsigned short int yPos = atoi(&words[1][1]);
	if (Table->checkBounds(xPos, yPos)) {



		//set a1 =SUM(range)
		//Check if input creates an Aggregate Function
		if ((words[2][0] == '=') && (Aggregate_Cell::findAggregateFunctionType(words[2].substr(1, 3)) != -1)) {
			std::cout << "Input creates aggregate cell\n";
			std::cout << "words[2].substr " << words[2].substr(1, 4);
			int functionType = Aggregate_Cell::findAggregateFunctionType(words[2].substr(1, 3));
			std::string AggregateString = words[2];
			Table->promoteCellToAggregate(Table, yPos, xPos, functionType, AggregateString);

		}
		//Using default Cell
		else {

			std::cout << "default cell\n";
			if (words.size() >= 3) {
				std::string toSet = input.substr(input.find(words[2], input.find(words[1]) + words[1].size()));

				//Check if Cell is Aggregate, if yes denote it to basic Cell
				if (dynamic_cast<Aggregate_Cell*>(Table->getCellObject(xPos - 1, yPos - 1))) {
					std::cout << "Cell is Aggregate\n";
					Table->demoteAggregateToCell(yPos, xPos, toSet);
					std::cout << "demoting\n";
				}
				else {
					std::cout << "Cell is basic\n";
					Table->setCell(xPos, yPos, toSet);
				}
			}
			else
				std::cout << "\nUnknown Command!" << std::endl;
		}
	}

}