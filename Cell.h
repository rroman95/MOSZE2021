#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<string>
#include<map>
#include<regex>
#include<climits>

class myTable;

class Cell {
public:
	std::string data;
	char alignment;
	static const std::string emptyCellSymbol;

	/** Default constructor */
	Cell() : data(emptyCellSymbol), alignment('r') {}
	/** Parameterized constructor */
	Cell(std::string data) : data(data), alignment('r') {}

	/** Copy constructor for Cell class */
	Cell(const Cell& other) {
		this->data = other.data;
		this->alignment = other.alignment;
	}

	/** Copy constructor for Cell class */
	Cell(const Cell* other) {
		this->data = other->data;
		this->alignment = other->alignment;
	}

	/** Assignment Operator & Self-Assignment check */
	Cell& operator=(const Cell& other) {
		std::cout << "Calling Assignment Operator Overload\n";
		if (this == &other)
			return *this;

		this->data = other.data;
		this->alignment = other.alignment;
		return *this;
	}

	virtual ~Cell() {}

	virtual std::string printCell() { return data.substr(0,data.find(".")+4); };
	//virtual std::string getCellData() { return data.substr(0, data.find(".") + 4); }
	virtual std::string getCellData() const { return data; }

	char getCellAlignment() const { return alignment; }
};


class Aggregate_Cell : public Cell {
public:
	static std::map <std::string, int> aggregate_function_types;
	myTable* Table;
	int functionType;
	std::string range;
	std::string calculatedValue;

	std::string getCellData() const { return calculatedValue; }
	
	//CONSTRUCTOR
	Aggregate_Cell(std::string data, myTable* Table, int functionType);
	
	//DESTRUCTOR
	~Aggregate_Cell() {}

	//FUNCTION TYPES
	static int findAggregateFunctionType(const std::string& input);
	void sumFunction();
	void avgFunction();
	void maxFunction();
	void minFunction();
	

	void getCellsInRange();

	//PRINT CELL
	std::string printCell();
	//std::string calculateAggregate() { return "aggregate found"; };

	//CALCULATE Cells in Range
	void calculateCellsInRange();

	bool isNumber(const std::string& str);

	//RANGE CHECKING
	static bool isValidRangeFormat(const std::string& str);
	static std::pair<std::string, std::string> getRangeCornerStrings(const std::string& range);
	static std::tuple<int, int, int, int> getRangeCornerInts(const std::string& range);
	//void calculateAggregate(myTable* Table);




		float sumElementsInRange{};

}; 


#endif


