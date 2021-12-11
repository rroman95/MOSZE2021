#ifndef MYTABLE_H
#define MYTABLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include <string>
#include <iomanip>
#include "Cell.h"

class Cell;

class myTable {
private:
	int row;
	int column;
	std::string name;
	std::vector<std::vector<Cell*>> Cells;
	static const std::string columnLetters;
	std::vector<unsigned int> maxLengthOfColumns;

public:

		bool checkBounds(int xPos, int yPos) {
			if ((yPos < 1 || xPos < 1) || (yPos > getRow() || xPos > getColumn())) {
				std::cout << "\nCell doesn't exist" << std::endl;
				return 0;
			}
			else { return 1; }

		}

	/** Default myTable with 1x1 dimensions, consisting of one Cell */
	myTable(std::string name) : row(1), column(1), name(name) {
		Cells.push_back(std::vector<Cell*>());
		Cells[0].push_back(new Cell(Cell::emptyCellSymbol));
		maxLengthOfColumns.push_back(1);
	}
	/** Destructor */
	~myTable() {
		for (unsigned int i = 0; i < Cells.size(); i++)
			for (unsigned int j = 0; j < Cells[i].size(); j++) {
				
				Cell* toDelete = Cells[i][j];
				delete toDelete;
			}
	}

	/** Parameterized constructor for creating N x M table */
	myTable(int rowCount, int columnCount) : row(rowCount), column(columnCount) {
		std::cout << "Calling parameterized function of myTable\n";
		setRow(rowCount);
		setColumn(columnCount);

		Cells.reserve(getRow());

		Cells.resize(getRow(), std::vector<Cell*>());

		std::cout << "creating Cells\n";

		for (int i = 0; i < getRow(); i++){
			Cells[i].reserve(getColumn());
			for (int j = 0; j < getColumn(); j++) {
				Cells[i].push_back(new Cell(Cell::emptyCellSymbol));
			}
		}

		maxLengthOfColumns.resize(columnCount, 1);
	}

	/** Copy constructor blocked */
	myTable(const myTable& other) = delete;
	/** Assignment operator blocked */
	myTable& operator=(const myTable&) = delete;


	std::string getName() const { return name; }
	/** returns the Tables width */
	int getRow() const { return row; }
	/** returns the tables depth */
	int getColumn() const { return column; }
	/** Set Row size to toSet */
	void setRow(int toSet) { row = toSet; }
	/** Set Column size to toSet */
	void setColumn(int toSet) { column = toSet; }
	/** Sets Cells data to toSet at pos[xPos,yPos] */
	void setCell(int yPos, int xPos, std::string const& toSet);
	/** Sets Cells alignment to _alignment (l for left, r for right) at pos [xPos, yPos] */
	void setCellAlignment(int yPos, int xPos, const char _alignment);



	/** returns the Cells data at pos[xPos,yPos] */
	std::string getCell(int yPos, int xPos) {

		if ((yPos < 0 || xPos < 0) || (xPos > getRow()-1 || yPos > getColumn()-1)) {
			std::cout << "Cell doesn't exist at pos: " << char(yPos + 'A' - 1) << xPos << std::endl;
			return ""; 
		}
		else {
			return Cells[xPos][yPos]->data;
		}
	}

	/** Returns the Cell as object at pos[xPos, yPos] */
	Cell *getCellObject(int yPos, int xPos) {
			return Cells[xPos][yPos];
	}

	void swapElements(int yPos_A, int xPos_A, int yPos_B, int xPos_B ) {
		std::cout << "Swapping Elements\n";
		Cell* temp = Cells[xPos_A][yPos_A];
		Cells[xPos_A][yPos_A] = Cells[xPos_B][yPos_B];
		Cells[xPos_B][yPos_B] = temp;

	}

	/** Checks every columns maximum length */
	void checkColumnsMaxLength(); 

	/** Adds rows to the Table */
	void addRows(int);
	/** Adds columns to the Table */
	void addColumns(int);
	/** Inserts rows after the given row */
	void insertRowsAfter(int, int);
	/** Inserts rows before the given row */
	void insertRowsBefore(int, int);
	/** Inserts columns after the given column */
	void insertColumnsAfter(int, int);
	/** Inserts columns before the given column */
	void insertColumnsBefore(int, int);
	/** Deletes the given row */
	void deleteRow(int);
	/** Deletes the given column */
	void deleteColumn(int);
	/** Sorts the Table's columns by the given row */
	void sortRow(int, bool);
	void swapCurrentColumnWithNext(unsigned int);
	/** Sorts the Table's rows by the given column */
	void sortColumn(int, bool);
	/** Resets the given Cell */
	void resetCell(int, int);
	/** Checks if the given Cell exists */
	bool cellExists(int, int);

	/** Swaps two Cell's content (string) */
	void swapCell(Cell*, Cell*);
	/** Checks if the given string is a number or a real string */
	bool isString(const std::string&);

	/** Prints the Table's size */
	void printTableSpecs() {
		std::cout << "Rows: " << Cells.size() << " Columns: " << Cells[0].size() << std::endl;
	}
	/** Prints the Table (linux, macos) */
	void printTable() const;
	/** Prints the Table (windows) */
	void printTableWin() const;
	/** Prints the Cell's content */
	void printCell(int xPos, int yPos) const { std::cout << "lol" << " "; }
	

	//AGGREGATE CELL FUNCTIONS
	void promoteCellToAggregate(myTable* Table, int yPos, int xPos, int functionType, std::string AggregateString);
	void demoteAggregateToCell(int yPos, int xPos, std::string const& toSet);

	void promoteCellsAfterFileParsing(myTable* Table);

};

#endif
