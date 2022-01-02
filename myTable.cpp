#include "myTable.h"
#include "Cell.h"

const std::string myTable::columnLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string Cell::emptyCellSymbol = "";

std::string printIt(std::string str, const int num) {
	std::string toReturn = "";
	for (int i = 0; i < num; i++) {
		toReturn += str;
	}
	return toReturn;
}

void myTable::checkColumnsMaxLength() {
	std::fill(maxLengthOfColumns.begin(), maxLengthOfColumns.end(), 1);

	for (int i = 0; i < getColumn(); i++) {
		for (int j = 0; j < getRow(); j++) {
			if (Cells[j][i]->data.size() > maxLengthOfColumns[i])
				maxLengthOfColumns[i] = Cells[j][i]->data.size();
		}
	}
}

void myTable::swapCell(Cell* a, Cell* b) {
    Cell t = *a;
    *a = *b;
    *b = t;
}


bool myTable::isString(const std::string& str)
{
	std::string validNum = "[0-9]*[.]?[0-9]*";

	if (str == ".")
		return true;
	else if (std::regex_match(str, std::regex(validNum)))
		return false;
	else
		return true;
	/*if (str == "") return true;
    for (char const &c : str) {
		if (c == '.') continue;
        else if (!std::isdigit(c)) return true;
    }
    return false;*/
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
			if(Cells[i][j]->alignment == 'l'){ // Cell ALIGNMENT = 'l'
			std::cout << Cells[i][j]->printCell() << printIt(" ", maxLengthOfColumns[j] - Cells[i][j]->data.length()) << "┃";
			}
			else { // Cell ALIGNMENT = 'r'
			std::cout  << printIt(" ", maxLengthOfColumns[j] - Cells[i][j]->data.length()) << Cells[i][j]->printCell() << "┃";
			}
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

void myTable::printTableWin() const {
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
			
			if(Cells[i][j]->alignment == 'l'){ // Cell ALIGNMENT = 'l'
			
				/*if (dynamic_cast<Aggregate_Cell*>(Cells[i][j]))
					std::cout << "A ";
				else
					std::cout << "C ";*/
			std::cout << Cells[i][j]->getCellData() << printIt(" ", maxLengthOfColumns[j] - Cells[i][j]->getCellData().length()) << "|";
			}
			else { // Cell ALIGNMENT = 'r'

				/*if (dynamic_cast<Aggregate_Cell*>(Cells[i][j]))
					std::cout << "A ";
				else
					std::cout << "C ";*/
			std::cout  << printIt(" ", maxLengthOfColumns[j] - Cells[i][j]->getCellData().length()) <<
				Cells[i][j]->getCellData() << "|";
			}
			//std::cout << "Width: " << Cells[i].size();
		}
		std::cout << std::endl;
		
	}

	// table bottom
	std::cout << "-" << ((getRow() > 9) ? "--" : "-");
	for (int i = 0; i < getColumn(); i++) {
		std::cout << "-" << printIt("-", maxLengthOfColumns[i]);
	}
	std::cout << "-" << std::endl;
	
	int numOfCells = 0;

	for (unsigned int i = 0; i < Cells.size(); i++)
		numOfCells += Cells[i].size();

	std::cout << "Number of Cells: " << numOfCells << "\n";

}


void myTable::addRows(int toAdd) {
	Cells.reserve(getRow() + toAdd);

	Cells.resize(getRow() + toAdd, std::vector<Cell*>());

	setRow(getRow() + toAdd);

	for (int j = 0; j < getRow(); j++) {
		int tmp = Cells[j].size();
		for (int i = 0; i < getColumn() - tmp; i++) {
			Cells[j].push_back(new Cell(Cell::emptyCellSymbol));
			
		}
	}
}

void myTable::addColumns(int toAdd) {
	if (getColumn() + toAdd > 26)
		std::cout << "\nColumn size exceeds limit" << std::endl;
	else {
		for (int i = 0; i < getRow(); i++) {

			Cells[i].reserve(getColumn() + toAdd);
			for (int j = 0; j < toAdd ; j++) {
				Cells[i].emplace_back(new Cell(Cell::emptyCellSymbol));
			}
		}
		setColumn(getColumn() + toAdd);

		for (int i = 0; i < toAdd; i++){
			maxLengthOfColumns.push_back(1);
		}
	}
}

void myTable::deleteRow(int toDelete) {
	if (toDelete > getRow() || toDelete < 1)
		std::cout << "\nRow doesn't exist" << std::endl;
	else {
		std::vector<Cell*> cellsToDelete = Cells[toDelete - 1]; // storing Cells to temporary vector

		auto iterator = Cells.begin() + toDelete - 1;

		Cells.erase(iterator);
		setRow(getRow() - 1);

		for (const auto& i : cellsToDelete)
			delete i;
	}
	
	checkColumnsMaxLength();
}

void myTable::deleteColumn(int toDelete) {
	if (toDelete > getColumn() || toDelete < 1)
		std::cout << "\nColumn doesn't exist" << std::endl;
	else {
		std::vector<Cell*> cellsToDelete;

		for (int i = 0; i < getRow(); i++) {
			cellsToDelete.emplace_back(Cells[i][toDelete - 1]);
			Cells[i].erase(Cells[i].begin() + toDelete - 1);
		}
		setColumn(getColumn() - 1);

		maxLengthOfColumns.erase(maxLengthOfColumns.begin() + toDelete - 1);

		for (const auto& i: cellsToDelete)
			delete i;
	}

}

void myTable::setCell(int yPos, int xPos, std::string const& toSet) {
	if ((yPos < 1 || xPos < 1) || (xPos > getRow() || yPos > getColumn()))
		std::cout << "\nCell doesn't exist" << std::endl;
	else {
		Cells[xPos - 1][yPos - 1]->data = toSet;

		if (toSet.length() > maxLengthOfColumns[yPos - 1]) 
			maxLengthOfColumns[yPos - 1] = toSet.length();
	}
}

void myTable::setCellAlignment(int xPos, int yPos, const char alignmentToSet) {
	if ((yPos < 0 || xPos < 0) || (xPos > getColumn()-1 || yPos > getRow()-1))
		std::cout << "\nCell doesn't exist" << std::endl;
	else 
		Cells[yPos][xPos]->alignment = alignmentToSet;
}

void myTable::insertRowsAfter(int toAdd, int wheretoAdd) {
	// Check if position wheretoAdd exists
	if ((wheretoAdd > getRow()) || (wheretoAdd < 1 ))
		std::cout << "\nRow to add after doesn't exist" << std::endl;
	else { // if position exist add N rows after Position:wheretoAdd
		Cells.insert(Cells.begin() + wheretoAdd, toAdd, std::vector<Cell*> (getColumn(),new Cell(Cell::emptyCellSymbol)));
		setRow(getRow() + toAdd);
	}
}

void myTable::insertRowsBefore(int toAdd, int wheretoAdd) {
	//Check if position wheretoAdd exists
	if ((wheretoAdd > getRow()) || (wheretoAdd < 1))
		std::cout << "\nRow to add before doesn't exist" << std::endl;
	else { // if position exist add N rows after Position:wheretoAdd
		Cells.insert(Cells.begin() + wheretoAdd - 1, toAdd, std::vector<Cell*>(getColumn(), new Cell(Cell::emptyCellSymbol)));
		setRow(getRow() + toAdd);
	}
}

void myTable::insertColumnsAfter(int toAdd, int wheretoAdd) {
	//Check if position wheretoAdd exists
	if ((wheretoAdd > getColumn()) || (wheretoAdd < 1))
		std::cout << "\nColumn to add after doesn't exist" << std::endl;
	else { // if position exist add N rows after Position:wheretoAdd
		for (int i = 0; i < getRow(); i++) {
			Cells[i].insert(Cells[i].begin() + wheretoAdd, toAdd, new Cell(Cell::emptyCellSymbol));
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
			Cells[i].insert(Cells[i].begin() + wheretoAdd - 1, toAdd,new Cell(Cell::emptyCellSymbol));
		}
		setColumn(getColumn() + toAdd);

		for (int i = 0; i < toAdd; i++) {
			maxLengthOfColumns.insert(maxLengthOfColumns.begin() + wheretoAdd - 1, 1);
		}
	}
}

bool isNumber(const std::string& strr) {
	std::string validNum = "[+-]?[0-9]*[.]?[0-9]*";
	if (strr == "" || strr == ".")
		return false;
	else if (std::regex_match(strr, std::regex(validNum)))
		return true;
	else
		return false;

}

struct sortingPolicyContainer {

	int rowToSort;
	bool isAsc;
	sortingPolicyContainer(int rowToSort, bool isAsc) :rowToSort(rowToSort), isAsc(isAsc) {}

	bool operator()(const std::vector<Cell*>& v1, const std::vector<Cell*>& v2) {
		if (isAsc == true) { //DESCENDING ORDER
				if (isNumber(v1[rowToSort]->getCellData()) && isNumber(v2[rowToSort]->getCellData())) {// NUMBER & NUMBER
					return stof(v1[rowToSort]->getCellData()) < stof(v2[rowToSort]->getCellData());
				}

				else if (isNumber(v1[rowToSort]->getCellData()) && !isNumber(v2[rowToSort]->getCellData())) {//NUMBER & STRING
					return false;
				}
				else if (!isNumber(v1[rowToSort]->getCellData()) && isNumber(v2[rowToSort]->getCellData())) {//STRING & NUMBER
					return true;
				}

				else if (!isNumber(v1[rowToSort]->getCellData()) && !isNumber(v2[rowToSort]->getCellData())) // STRING & STRING
					return v1[rowToSort]->getCellData() < v2[rowToSort]->getCellData();

			}
		else { // ASCENDING
			if (isNumber(v1[rowToSort]->getCellData()) && isNumber(v2[rowToSort]->getCellData())) {// NUMBER & NUMBER
				return stof(v1[rowToSort]->getCellData()) > stof(v2[rowToSort]->getCellData());
			}

			else if (isNumber(v1[rowToSort]->getCellData()) && !isNumber(v2[rowToSort]->getCellData())) {//NUMBER & STRING
				return true;
			}
			else if (!isNumber(v1[rowToSort]->getCellData()) && isNumber(v2[rowToSort]->getCellData())) {//STRING & NUMBER
				return false;
			}

			else if (!isNumber(v1[rowToSort]->getCellData()) && !isNumber(v2[rowToSort]->getCellData())) // STRING & STRING
				return v1[rowToSort]->getCellData() > v2[rowToSort]->getCellData();
		}

		return true; // Default return value
	}
};



void myTable::sortColumn(int toSort, bool isAsc) {
	std::cout << "Sort by Columns\n";
	if (toSort > getColumn()-1 || toSort < 0)
        std::cout << "\nRow doesn't exist" << std::endl;
    else {
		sort(Cells.begin(), Cells.end(), sortingPolicyContainer(toSort,isAsc));
	}
	
	checkColumnsMaxLength();
}

void myTable::swapCurrentColumnWithNext(unsigned int currentCol) {
	std::cout << "Swapping\n";
	std::vector<Cell*> tempColumn;
	//Pushing current Column into temporary Vector
	for (unsigned int rowIter = 0; rowIter < Cells.size(); rowIter++)
		tempColumn.push_back(Cells[rowIter][currentCol]);

	for (const auto& i : tempColumn) {
		std::cout << i->getCellData() << "\n";

	}

	//Overwriting current Column with next Column
	for (unsigned int rowIter = 0; rowIter < Cells.size(); rowIter++) {
		Cells[rowIter][currentCol] = Cells[rowIter][currentCol + 1];

	}

	//Swapping with next column
	for (unsigned int rowIter = 0; rowIter < Cells.size(); rowIter++) {
		Cells[rowIter][currentCol + 1] = tempColumn[rowIter];

	}
}

bool sortingPolicyForRows(const Cell* Cell1, const Cell* Cell2, bool isAsc) {

		if (isAsc == false) { //DESCENDING ORDER
			if (isNumber(Cell1->getCellData()) && isNumber(Cell2->getCellData())) {// NUMBER & NUMBER
				return stof(Cell1->getCellData()) < stof(Cell2->getCellData());
			}

			else if (isNumber(Cell1->getCellData()) && !isNumber(Cell2->getCellData())) {//NUMBER & STRING
				return false;
			}
			else if (!isNumber(Cell1->getCellData()) && isNumber(Cell2->getCellData())) {//STRING & NUMBER
				return true;
			}

			else if (!isNumber(Cell1->getCellData()) && !isNumber(Cell2->getCellData())) // STRING & STRING
				return Cell1->getCellData() < Cell2->getCellData();

		}
		else { // ASCENDING
			if (isNumber(Cell1->getCellData()) && isNumber(Cell2->getCellData())) {// NUMBER & NUMBER
				return stof(Cell1->getCellData()) > stof(Cell2->getCellData());
			}

			else if (isNumber(Cell1->getCellData()) && !isNumber(Cell2->getCellData())) {//NUMBER & STRING
				return true;
			}
			else if (!isNumber(Cell1->getCellData()) && isNumber(Cell2->getCellData())) {//STRING & NUMBER
				return false;
			}

			else if (!isNumber(Cell1->getCellData()) && !isNumber(Cell2->getCellData())) // STRING & STRING
				return Cell1->getCellData() > Cell2->getCellData();
		}
		return true; // Default return value

	}

void myTable::sortRow(int toSort, bool isAsc) {
	if (toSort > getRow() - 1 || toSort < 0)
		std::cout << "\nColumn doesn't exist" << std::endl;
	else {
		std::cout << "Sort by Rows\n";

		//Lazy BubbleSort implementation
		for (unsigned int numOfIters = 0; numOfIters  < Cells[toSort].size(); numOfIters++) {
			for (unsigned int currentCol = 0; currentCol < Cells[toSort].size() - 1; currentCol++)
			{
				if(sortingPolicyForRows(Cells[toSort][currentCol], Cells[toSort][currentCol+1],isAsc)) {
					swapCurrentColumnWithNext(currentCol);
				}
			}
		}
		checkColumnsMaxLength();
	}
}

void myTable::resetCell(int x, int y) {
	Cells[x][y]->data = "";
}

bool myTable::cellExists(int x, int y) {
	if (x < 0 || x > getColumn()-1) return false;
	else if (y < 0 || y > getRow()-1) return false;
	else return true;
}

//AGGREGATE CELL FUNCTIONS

void myTable::promoteCellToAggregate(myTable* Table, int yPos, int xPos,int functionType, std::string AggregateString) {
	if ((yPos < 1 || xPos < 1) || (yPos > getRow() || xPos > getColumn()))
		std::cout << "\nCell doesn't exist" << std::endl;
	
	else {
		std::cout << "Promoting cell\n";
		Cell* toDelete = getCellObject(xPos - 1, yPos - 1);
		Cells[yPos - 1].insert(Cells[yPos - 1].begin()+ xPos - 1, new Aggregate_Cell(AggregateString, Table , functionType ));
		Cells[yPos - 1].erase(Cells[yPos - 1].begin() + xPos);
		delete toDelete;

	}
}

void myTable::demoteAggregateToCell(int yPos, int xPos, std::string const& toSet) {
	if ((yPos < 1 || xPos < 1) || (yPos > getRow() || xPos > getColumn()))
		std::cout << "\nCell doesn't exist" << std::endl;
	else {
		std::cout << "Demoting cell\n";
		Cell* toDelete = getCellObject(xPos - 1, yPos - 1);
		Cells[yPos - 1].insert(Cells[yPos - 1].begin() + xPos - 1, new Cell(toSet));
		Cells[yPos - 1].erase(Cells[yPos - 1].begin() + xPos);
		delete toDelete;
	}
}

void myTable::promoteCellsAfterFileParsing(myTable* Table) {
	//std::cout << Cells[0].size() << " : " <<
	for (unsigned int i = 0; i < Cells.size(); i++)
		for (unsigned int j = 0; j < Cells[i].size(); j++) {

			std::string currentCellData = Cells[i][j]->data;

			//edit a1 =SUM
			//Check if data in Cell creates an Aggregate Function
			if ((currentCellData[0] == '=') && (Aggregate_Cell::findAggregateFunctionType(currentCellData.substr(1, 3)) != -1)) {
				std::cout << "Input creates aggregate cell\n";
				std::cout << "words[2].substr " << currentCellData.substr(1, 4);
				int functionType = Aggregate_Cell::findAggregateFunctionType(currentCellData.substr(1, 3));
				std::string AggregateString = currentCellData;
				Table->promoteCellToAggregate(Table, i+1, j+1, functionType, AggregateString);

			}
		}

}

/*
void myTable::calculateAggregateCells() {
	for(int i = 0;i<Cells[0].size();i++)
		for (int j = 0; j < Cells[0].size(); j++) {
			if (!dynamic_cast<Aggregate_Cell*>(Cells[i][j])) {
				continue;
				//Does Nothing if current Cell is not of Aggregate type
			}
			else {
				Aggregate_Cell* ptr = dynamic_cast<Aggregate_Cell*>(Cells[i][j]);
				std::cout << ptr->data << "DATA\n";
			}
		}
}
*/
