#include "myTable.h"

const std::string myTable::columnLetters = "ABCDEFGHIJ";
const std::string myTable::emptyCellSymbol = "_";

void myTable::printTable() const{
	std::cout << "-------TABLE-------" << std::endl;
	
	std::cout << "  ";
	for (int i = 0; i < getColumn(); i++) {  // ROW Lettering
		std::cout << columnLetters[i] << "\t" << "  ";
	}
	std::cout << std::endl;
	

	for (unsigned int i = 0; i < Cells.size(); i++) {              //       "\t"
		std::cout << i + 1 << " ";
		for (unsigned int j = 0; j < Cells[i].size(); j++) {

			if (Cells[i][j].size() > 8)
				std::cout << Cells[i][j].substr(0, 6) << "..";	// If Cell is too big, truncate it
			else
				std::cout << Cells[i][j] << "\t" << "  ";       // Compensating for Tabulator Spacing

		}
		std::cout << Cells[i].size() << std::endl;
		std::cout << std::endl;
	}
	std::cout << "-------------------" << std::endl;
}

void myTable::addRows(int toAdd) {
	if (getRow() + toAdd > 9)				// 26-ot kell tudnia kezelni !!!!!!!!!!!!
		std::cout << "Column size exceeds limit." << std::endl;
	else {
		Cells.resize((getRow() + toAdd), std::vector<std::string>(getColumn(), emptyCellSymbol));    // 0 --- az új Cellákat 0 intekkel tölti fel
		setRow(getRow() + toAdd);
	}
}

void myTable::addColumns(int toAdd) {

	if (getColumn() + toAdd > 10)
		std::cout << "Column size exceeds limit." << std::endl;
	else {
		for (int i = 0; i < getRow(); i++) {
			Cells[i].resize((getColumn() + toAdd), emptyCellSymbol);
		}
		setColumn(getColumn() + toAdd);
	}
}

void myTable::deleteRow(int toDelete) {
	if (toDelete > getRow() || toDelete == 0)
		std::cout << "Row doesn't exist" << std::endl;
	else {
	auto iterator = Cells.begin()+toDelete - 1 ;
	Cells.erase(iterator);
	setRow(getRow() - 1);
	}
}

void myTable::deleteColumn(int toDelete) {
	std::cout << "Column deletiong thingy" << std::endl;
	if (toDelete > getColumn() || toDelete == 0)
		std::cout << "Column doesn't exist" << std::endl;
	else {
		for(int i = 0;i < getRow();i++)
			Cells[i].erase(Cells[i].begin()+toDelete-1);
		setColumn(getColumn() - 1);
	}
}

void myTable::setCell(int yPos, int xPos, std::string const& toSet) {

	//Check if Cells exist
	std::cout << yPos << " > " <<getRow() << " --- "<< xPos << " > " << getColumn() <<  std::endl;

	if ((yPos < 1 || xPos < 1) || (xPos > getRow() || yPos > getColumn()))
		std::cout << "Cell doesn't exist" << std::endl;

	//If Exist set it to toSet val
	else
		Cells[xPos-1][yPos-1] = toSet; 

}
