#include "myTable.h"

const std::string myTable::columnLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string myTable::emptyCellSymbol = "";

std::string printIt(std::string str, const int num) {
	std::string toReturn = "";
	for (int i = 0; i < num; i++) {
		toReturn += str;
	}
	return toReturn;
}

void myTable::printTable() const {
	// table top
	std::cout << "\n┏" << ((getRow() > 9) ? "━━" : "━");
	for (int i = 0; i < getColumn(); i++) {
		std::cout << "┳" << printIt("━", maxLengthOfColumns[i]);
	}
	std::cout << "┓" << std::endl;

	// letters
	std::cout << "┃" << ((getRow() > 9) ? "  ┃" : " ┃");
	for (int i = 0; i < getColumn(); i++) {
		std::cout << columnLetters[i] 
		<< printIt(" ", maxLengthOfColumns[(columnLetters[i] - 'A')] - 1) << "┃";
	}
	std::cout << std::endl;

	// row line and numbers
	for (unsigned int i = 0; i < Cells.size(); i++) {
		std::cout << "┣" << ((getRow() > 9) ? "━━" : "━");
		for (unsigned int j = 0; j < Cells[i].size(); j++) {
			std::cout << "╋" << printIt("━", maxLengthOfColumns[j]);
		}
		std::cout << "┫" << std::endl;
		
		std::cout << "┃" << i + 1 << ((i < 9 && getRow() > 9) ? " " : "") << "┃";
	// table content
		for (unsigned int j = 0; j < Cells[i].size(); j++) {
			std::cout << Cells[i][j] 
			<< printIt(" ", maxLengthOfColumns[j] - Cells[i][j].length()) 
			<< "┃";
		}
		std::cout << std::endl;
	}

	// table bottom
	std::cout << "┗" << ((getRow() > 9) ? "━━" : "━");
	for (int i = 0; i < getColumn(); i++) {
		std::cout << "┻" << printIt("━", maxLengthOfColumns[i]);
	}
	std::cout << "┛" << std::endl;
}

void myTable::printTableWin() const { // Bocsi Dávid, de kiszedtem a + jeleket, mert baszták a szememet :(
	// table top
	std::cout << "\n-" << ((getRow() > 9) ? "--" : "-");
	for (int i = 0; i < getColumn(); i++) {
		std::cout << "-" << printIt("-", maxLengthOfColumns[i]);
	}
	std::cout << "-" << std::endl;

	// letters
	std::cout << "|" << ((getRow() > 9) ? "  |" : " |");
	for (int i = 0; i < getColumn(); i++) {
		std::cout << columnLetters[i] 
		<< printIt(" ", maxLengthOfColumns[(columnLetters[i] - 'A')] - 1) << "|";
	}
	std::cout << std::endl;

	// row line and numbers
	for (unsigned int i = 0; i < Cells.size(); i++) {
		std::cout << "-" << ((getRow() > 9) ? "--" : "-");
		for (unsigned int j = 0; j < Cells[i].size(); j++) {
			std::cout << "-" << printIt("-", maxLengthOfColumns[j]);
		}
		std::cout << "-" << std::endl;
		
		std::cout << "|" << i + 1 << ((i < 9 && getRow() > 9) ? " " : "") << "|";
	// table content
		for (unsigned int j = 0; j < Cells[i].size(); j++) {
			std::cout << Cells[i][j] 
			<< printIt(" ", maxLengthOfColumns[j] - Cells[i][j].length()) 
			<< "|";
		}
		std::cout << std::endl;
	}

	// table bottom
	std::cout << "-" << ((getRow() > 9) ? "--" : "-");
	for (int i = 0; i < getColumn(); i++) {
		std::cout << "-" << printIt("-", maxLengthOfColumns[i]);
	}
	std::cout << "-" << std::endl;
}

void myTable::addRows(int toAdd) {
	Cells.resize((getRow() + toAdd), std::vector<std::string>(getColumn(), emptyCellSymbol));
	setRow(getRow() + toAdd);
}

void myTable::addColumns(int toAdd) {
	if (getColumn() + toAdd > 26)
		std::cout << "\nColumn size exceeds limit" << std::endl;
	else {
		for (int i = 0; i < getRow(); i++) {
			Cells[i].resize((getColumn() + toAdd), emptyCellSymbol);
		}
		setColumn(getColumn() + toAdd);

		for (int i = 0; i < toAdd; i++){
			maxLengthOfColumns.push_back(1);
		}
	}
}

void myTable::deleteRow(int toDelete) {
	if (toDelete > getRow() || toDelete == 0)
		std::cout << "\nRow doesn't exist" << std::endl;
	else {
		auto iterator = Cells.begin() + toDelete - 1;
		Cells.erase(iterator);
		setRow(getRow() - 1);
	}
	
	std::fill(maxLengthOfColumns.begin(), maxLengthOfColumns.end(), 1);
	for (int i = 0; i < getColumn(); i++) {
		for (int j = 0; j < getRow(); j++) {
			if (Cells[j][i].size() > maxLengthOfColumns[i])
				maxLengthOfColumns[i] = Cells[j][i].size();
		}
	}
}

void myTable::deleteColumn(int toDelete) {
	if (toDelete > getColumn() || toDelete == 0)
		std::cout << "\nColumn doesn't exist" << std::endl;
	else {
		for (int i = 0; i < getRow(); i++)
			Cells[i].erase(Cells[i].begin() + toDelete - 1);
		setColumn(getColumn() - 1);

		maxLengthOfColumns.erase(maxLengthOfColumns.begin() + toDelete - 1);
	}


}

void myTable::setCell(int yPos, int xPos, std::string const& toSet) {
	if ((yPos < 1 || xPos < 1) || (xPos > getRow() || yPos > getColumn()))
		std::cout << "\nCell doesn't exist" << std::endl;
	else {
		Cells[xPos - 1][yPos - 1] = toSet;

		if (toSet.length() > maxLengthOfColumns[yPos - 1]) 
			maxLengthOfColumns[yPos - 1] = toSet.length();
	}
}

void myTable::insertRowsAfter(int toAdd, int wheretoAdd) {
	// Check if position wheretoAdd exists
	if ((wheretoAdd > getRow()) || (wheretoAdd < 1 ))
		std::cout << "\nRow to add after doesn't exist" << std::endl;
	else { // if position exist add N rows after Position:wheretoAdd
		Cells.insert(Cells.begin() + wheretoAdd, toAdd, std::vector<std::string> (getColumn(), emptyCellSymbol));
		setRow(getRow() + toAdd);
	}
}

void myTable::insertRowsBefore(int toAdd, int wheretoAdd) {
	//Check if position wheretoAdd exists
	if ((wheretoAdd > getRow()) || (wheretoAdd < 1))
		std::cout << "\nRow to add before doesn't exist" << std::endl;
	else { // if position exist add N rows after Position:wheretoAdd
		Cells.insert(Cells.begin() + wheretoAdd - 1, toAdd, std::vector<std::string>(getColumn(), emptyCellSymbol));
		setRow(getRow() + toAdd);
	}
}

void myTable::insertColumnsAfter(int toAdd, int wheretoAdd) {
	//Check if position wheretoAdd exists
	if ((wheretoAdd > getColumn()) || (wheretoAdd < 1))
		std::cout << "\nColumn to add after doesn't exist" << std::endl;
	else { // if position exist add N rows after Position:wheretoAdd
		for (int i = 0; i < getRow(); i++) {
			Cells[i].insert(Cells[i].begin() + wheretoAdd, toAdd, emptyCellSymbol);
		}
		setColumn(getColumn() + toAdd);

		for (int i = 0; i < toAdd; i++) {
			maxLengthOfColumns.insert(maxLengthOfColumns.begin() + wheretoAdd, 1);
		}
	}
}

void myTable::insertColumnsBefore(int toAdd, int wheretoAdd) {
	//Check if position wheretoAdd exists
	if ((wheretoAdd > getColumn()) || (wheretoAdd < 1))
		std::cout << "\nColumn to add before doesn't exist " << std::endl;
	else { // if position exist add N rows after Position:wheretoAdd
		for (int i = 0; i < getRow(); i++) {
			Cells[i].insert(Cells[i].begin() + wheretoAdd - 1, toAdd, emptyCellSymbol);
		}
		setColumn(getColumn() + toAdd);

		for (int i = 0; i < toAdd; i++) {
			maxLengthOfColumns.insert(maxLengthOfColumns.begin() + wheretoAdd - 1, 1);
		}
	}
}
