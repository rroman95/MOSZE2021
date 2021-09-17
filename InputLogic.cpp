#include<iostream>
#include<string>
#include<vector>

void editLogic(myTable *Table ,int xPos ,int yPos ,int toSet) {
 // check if CELL exists                                                                        // Jó lenne, ha a myTable classon belül történne a Cella létezésének vizsgálata
	if ((xPos < 1  || yPos < 1) || ((Table->getRow() < xPos) || (Table->getColumn()  < yPos))) {
		std::cout << "Cell doesnt exist" << std::endl;
		return;
	}
// if CELL exists, set value to toSet
	else 
		Table->setCell(xPos-1, yPos-1, toSet);
	


}

void InputLogic(myTable *Table,std::string &input) {
	int xPos = -1;
	int yPos = -1;
	int pos = 0;
	pos = input.find("edit ");
	
	if (pos == 0) {
		xPos = int(input[5]) - 48;  // Nagyon csunya stiiil ez az int cast megoldas
		yPos = int(input[6]) - 48;	// fuj
		editLogic(Table, xPos, yPos, 1);
	}
	else if (input == "1")
		Table->addRows(1);
	else if (input == "2")
		Table->addColumns(1);
}