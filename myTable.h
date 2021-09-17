#ifndef MYTABLE_H
#define MYTABLE_H

#include<vector>
#include<iostream>

class myTable {
private:
	int row;
	int column;
	std::vector<std::vector<int>> Cells;

public:
	std::vector<std::vector<int>>* ptrToCells;
	int getRow() const{ return row; }
	int getColumn() const{ return column; }
	void setRow(int toSet) { row = toSet; }
	void setColumn(int toSet) { column = toSet; }
	void setCell(int yPos, int xPos, int toSet) { Cells[xPos][yPos] = 1; } //toSet "kikapcsolva" , minden setCell 1re állítja a választott cellát
	
	//DESTRUKTOR / Memória kezelés hiányzik

	void addRows(int);
	void addColumns(int);
	void resizeFirstRow(int);

	void printTableSpecs() { std::cout << "Rows: " << row << " Columns: " << column << std::endl; }
	void printTable() const;
	void printCell(int xPos, int yPos) const{ std::cout << Cells[xPos][yPos] << " "; }

	myTable() : row(1), column(1), ptrToCells(&Cells) {
		Cells.push_back(std::vector<int>());
		Cells[0].push_back(0);
	}

};

#endif // !MYTABLE_H

