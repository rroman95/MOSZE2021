#ifndef MYTABLE_H
#define MYTABLE_H

#include<vector>
#include<iostream>

/*
	  ------- SOR / ROW----->  Cells[i].push_back(var);
	|					  Cells[i].resize(size, var);
	|
	|
  OSZLOP
  COLUMN        Cells.push_back(vector<int>());
	|		    Cells.resize(size, vector<int>(0));
	|
	↓

*/

class myTable {
private:
	int row;
	int column;
	std::vector<std::vector<std::string>> Cells;
	static const std::string columnLetters;
	static const std::string emptyCellSymbol;

public:
	//std::vector<std::vector<std::string>>* ptrToCells;   // for future use
	int getRow() const { return row; }
	int getColumn() const { return column; }
	void setRow(int toSet) { row = toSet; }
	void setColumn(int toSet) { column = toSet; }
	void setCell(int yPos, int xPos, std::string const& toSet);

	//DESTRUKTOR missing/ Memória kezelés hiányzik maybe

	void addRows(int);
	void addColumns(int);

	void deleteRow(int);
	void deleteColumn(int);

	void printTableSpecs() {
		std::cout << "Rows: " << Cells[0].size() << " Columns: " << Cells.size() << std::endl;
		std::cout << "Rows: " << getRow() << " Columns: " << getColumn() << std::endl;
	}
	void printTable() const;
	void printCell(int xPos, int yPos) const { std::cout << Cells[xPos][yPos] << " "; }

	myTable() : row(1), column(1) {   //Default Constructor
		Cells.push_back(std::vector<std::string>());
		Cells[0].push_back(emptyCellSymbol);
	}

};

#endif // !MYTABLE_H
