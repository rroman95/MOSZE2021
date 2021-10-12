
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
	std::vector<unsigned int> maxLengthOfColumns;

public:
	myTable() : row(1), column(1) {
		Cells.push_back(std::vector<std::string>());
		Cells[0].push_back(emptyCellSymbol);
		maxLengthOfColumns.push_back(1);
	}
	~myTable() {}

	myTable(int rowCount, int columnCount) : row(rowCount), column(columnCount) {
		Cells.resize(rowCount, std::vector<std::string>(columnCount, emptyCellSymbol));
		maxLengthOfColumns.resize(columnCount, 1);
	}

	myTable(const myTable&) = delete;
	myTable& operator=(const myTable&) = delete;

	//std::vector<std::vector<std::string>>* ptrToCells;   // for future use
	int getRow() const { return row; }
	int getColumn() const { return column; }
	void setRow(int toSet) { row = toSet; }
	void setColumn(int toSet) { column = toSet; }
	void setCell(int yPos, int xPos, std::string const& toSet);

	std::string getCell(int yPos, int xPos) {	
		std::cout << yPos << " : " << xPos << std::endl;
		std::cout << xPos << " < " << getRow() << " : " << yPos << " < " << getColumn() << std::endl;
		if ((yPos < 1 || xPos < 1) || (xPos > getRow() || yPos > getColumn())) {
			std::cout << "Cell doesn't exist at pos: " << yPos << " : " << xPos << std::endl;
			return ""; 
		}
		else {
			return Cells[xPos - 1][yPos - 1];
		}
	}

	void addRows(int);
	void addColumns(int);
	void insertRowsAfter(int, int);
	void insertRowsBefore(int, int);
	void insertColumnsAfter(int, int);
	void insertColumnsBefore(int, int);
	void deleteRow(int);
	void deleteColumn(int);

	void printTableSpecs() {
		std::cout << "Rows: " << Cells.size() << " Columns: " << Cells[0].size() << std::endl;
		//std::cout << "getRows: " << getRow() << " getColumns: " << getColumn() << std::endl;
	}
	void printTable() const;
	void printTableWin() const;
	void printCell(int xPos, int yPos) const { std::cout << Cells[xPos][yPos] << " "; }

};

#endif
