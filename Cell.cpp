#include "Cell.h"
#include "myTable.h"

//STATIC DATA TYPES
std::map <std::string, int> Aggregate_Cell::aggregate_function_types =
{ {"SUM",1},
  {"AVG",2},
  {"MIN",3},
  {"MAX",4} };

//AGGREGATE_CELL CONSTRUCTOR
Aggregate_Cell::Aggregate_Cell(std::string data, myTable* Table, int functionType) :Cell(data), Table(Table), functionType(functionType), range("?:?"), calculatedValue("0") { getCellsInRange(); }



std::string Aggregate_Cell::printCell() {
	//return  "data: " + data + " calcValue: " + calculatedValue + " range: " + range + " " + std::to_string(functionType);
	return  calculatedValue;
}


//0123456789012
//=SUM(a1:b2)
void Aggregate_Cell::getCellsInRange() {



	if (data.size() < 5)
		calculatedValue = "Range?";
	else {
		std::string temp_range = data.substr(4, data.size() - 4);
		std::cout << "RANGE: " << temp_range << std::endl;


		if (!isValidRangeFormat(temp_range))
			calculatedValue = "#NAME?";
		else {
			range = temp_range.substr(1, temp_range.size() - 2);
			const auto& [topLeftLetter, bottomRightLetter, topLeftNumber, bottomRightNumber] = getRangeCornerInts(range);

			if (!(Table->cellExists(topLeftLetter, topLeftNumber)) || !(Table->cellExists(bottomRightLetter, bottomRightNumber)))
				calculatedValue = "#NAME?";
			else {
				//If Cells exist in given range, calculate them using member function calculateCellsInRange()
				//calculatedValue = "cells exist in range";
				std::cout << "Calculating cells in range\n";
				calculateCellsInRange();
			}
		}
	}
}

void Aggregate_Cell::calculateCellsInRange() {

	switch (functionType) {
	case 1:
		sumFunction();
		break;
	case 2:
		avgFunction();
		break;
	case 3:
		minFunction();
		break;
	case 4:
		maxFunction();
		break;

	}


}

//=SUM
void Aggregate_Cell::sumFunction(){ 
	const auto& [topLeftLetter, bottomRightLetter, topLeftNumber, bottomRightNumber] = getRangeCornerInts(range);
	float currentValidCellData = 0;

	for (int i = topLeftNumber; i < bottomRightNumber + 1; i++)
		for (int j = topLeftLetter; j < bottomRightLetter + 1; j++) {
			std::cout << i << ":" << j << " ";
			std::cout << Table->getCellObject(j, i)->getCellData() << " | ";

			if (isNumber(Table->getCellObject(j, i)->getCellData()))
				currentValidCellData += stof(Table->getCellObject(j, i)->getCellData());
			else
				continue;
		}
	calculatedValue = std::to_string(currentValidCellData);
}

//=AVG
void Aggregate_Cell::avgFunction(){
	std::cout << "break1\n";
	const auto& [topLeftLetter, bottomRightLetter, topLeftNumber, bottomRightNumber] = getRangeCornerInts(range);
	float currentValidCellData = 0;
	float numOfValidCells = 0;

	std::cout << "break2\n";

	for (int i = topLeftNumber; i < bottomRightNumber + 1; i++)
		for (int j = topLeftLetter; j < bottomRightLetter + 1; j++) {
			std::cout << i << ":" << j << " ";
			std::cout << Table->getCellObject(j, i)->getCellData() << " | ";

			if (isNumber(Table->getCellObject(j, i)->data)) {
				currentValidCellData += stof(Table->getCellObject(j, i)->getCellData());
				numOfValidCells++;
			}
			else
				continue;
		}
	
	calculatedValue = std::to_string(currentValidCellData/numOfValidCells);
	std::cout << "break3\n";
}

//=MAX
void Aggregate_Cell::maxFunction(){
	const auto& [topLeftLetter, bottomRightLetter, topLeftNumber, bottomRightNumber] = getRangeCornerInts(range);
	float currentValidCellData = 0;
	float currentMax = INT_MIN;

	for (int i = topLeftNumber; i < bottomRightNumber + 1; i++)
		for (int j = topLeftLetter; j < bottomRightLetter + 1; j++) {
			std::cout << i << ":" << j << " ";
			std::cout << Table->getCellObject(j, i)->getCellData() << " | ";

			if (isNumber(Table->getCellObject(j, i)->getCellData())) {
				currentValidCellData = stof(Table->getCellObject(j, i)->getCellData());
				if (currentValidCellData > currentMax)
					currentMax = currentValidCellData;
			}
			else
				continue;
		}
	calculatedValue = std::to_string(currentMax);
}

//=MIN
void Aggregate_Cell::minFunction(){
	const auto& [topLeftLetter, bottomRightLetter, topLeftNumber, bottomRightNumber] = getRangeCornerInts(range);
	float currentValidCellData = 0;
	float currentMin = (float)INT_MAX;

	for (int i = topLeftNumber; i < bottomRightNumber + 1; i++) 
		for (int j = topLeftLetter; j < bottomRightLetter + 1; j++) {
			std::cout << i << ":" << j << " ";
			std::cout << Table->getCellObject(j, i)->getCellData() << " | ";

			if (isNumber(Table->getCellObject(j, i)->getCellData())) {
				currentValidCellData = stof(Table->getCellObject(j, i)->getCellData());
				if (currentValidCellData < currentMin) {
					std::cout << "currentMin: " << currentMin << " : currentValidCellData: " <<  currentValidCellData << " ";
					currentMin = currentValidCellData;

				}
			}
			else
				continue;
		}
	std::cout << "currentMIN:" << currentMin << std::endl;
	calculatedValue = std::to_string(currentMin);
}


bool Aggregate_Cell::isNumber(const std::string& str)
{
	std::string validNum = "[0-9]*[.]?[0-9]+";

	if (str == ".")
		return false;
	else if (std::regex_match(str, std::regex(validNum)))
		return true;
	else
		return false;
	/*if (str == "") return false;
	for (char const &c : str) {
		if (c == '.') continue;
		else if (!std::isdigit(c)) return false;
	}
	return true;*/
}

/*for (int i = topLeftNumber; i < bottomRightNumber + 1; i++) {
	for (int j = topLeftLetter; j < bottomRightLetter + 1; j++) {
		Table->setCellAlignment(i, j, toSet);
	}
}
*/


int Aggregate_Cell::findAggregateFunctionType(const std::string &input) {

	//First -> string, Second -> int
	for (const auto& i : Aggregate_Cell::aggregate_function_types) {
		if (input == i.first)
			return i.second;
	}

	return -1;

}

bool Aggregate_Cell::isValidRangeFormat(const std::string& str) {
	std::string validReg = "[(][a-zA-Z][0-9]+:[a-zA-Z][0-9]+[)]";

	if (std::regex_match(str, std::regex(validReg))) {
		return true;
	}
	else {
		return false;
	}
}

std::pair<std::string, std::string> Aggregate_Cell::getRangeCornerStrings(const std::string& range) {
	return { range.substr(0, range.find(":")), range.substr(range.find(":") + 1) };
}

std::tuple<int, int, int, int> Aggregate_Cell::getRangeCornerInts(const std::string& range) {
	int topLeftLetter;
	int bottomRightLetter;
	int topLeftNumber;
	int bottomRightNumber;

	if (getRangeCornerStrings(range).first[0] < getRangeCornerStrings(range).second[0]) {
		topLeftLetter = (toupper(getRangeCornerStrings(range).first[0]) - 'A');
		bottomRightLetter = (toupper(getRangeCornerStrings(range).second[0]) - 'A');
	}
	else {
		bottomRightLetter = (toupper(getRangeCornerStrings(range).first[0]) - 'A');
		topLeftLetter = (toupper(getRangeCornerStrings(range).second[0]) - 'A');
	}
	if (std::stoi(getRangeCornerStrings(range).first.substr(1)) < std::stoi(getRangeCornerStrings(range).second.substr(1))) {
		topLeftNumber = std::stoi(getRangeCornerStrings(range).first.substr(1)) - 1;
		bottomRightNumber = std::stoi(getRangeCornerStrings(range).second.substr(1)) - 1;
	}
	else {
		bottomRightNumber = std::stoi(getRangeCornerStrings(range).first.substr(1)) - 1;
		topLeftNumber = std::stoi(getRangeCornerStrings(range).second.substr(1)) - 1;
	}

	return std::make_tuple(topLeftLetter, bottomRightLetter, topLeftNumber, bottomRightNumber);
}
/*
void Aggregate_Cell::calculateAggregate(myTable* Table) {
	std::cout << "Inside " << Table->
	data = 10;
}*/
