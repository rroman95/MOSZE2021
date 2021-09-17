#include "myTable.h"



void myTable::printTable() const{
	std::cout << "-------TABLE-------" << std::endl;
	for (int i = 0; i < Cells.size(); i++) {
		for (int j = 0; j < Cells[i].size(); j++) {
			std::cout << Cells[i][j] << " ";

		}
		std::cout << std::endl;
	}
	std::cout << "-------------------" << std::endl;
}

void myTable::addRows(int toAdd) {
	for (int i = 0; i < getColumn(); i++) {
			Cells[i].resize((getRow() + toAdd), 0);
	}
	setRow(getRow() + toAdd);
}

void myTable::addColumns(int toAdd) {

	Cells.resize((getColumn() + toAdd), std::vector<int>(getRow(),0));    // 0 --- az új Cellákat 0 intekkel tölti fel
	setColumn(getColumn() + toAdd);
}

void myTable::resizeFirstRow(int toAdd) {
	std::cout << "Resizing by " << toAdd << std::endl;
	Cells[0].resize((getRow() + toAdd), 1);
	setRow((getRow() + toAdd));
}