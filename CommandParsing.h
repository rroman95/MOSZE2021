#ifndef COMMANDPARSING_H
#define COMMANDPARSING_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <tuple>
#include "myTable.h"
#include "fileParsing.h"

class Commands {
public:
	std::map<std::string, int> command_codes;

	Commands() {
		command_codes.insert(std::pair<std::string, int>("edit", 1));
		command_codes.insert(std::pair<std::string, int>("add", 2));
		command_codes.insert(std::pair<std::string, int>("delete", 3));
		command_codes.insert(std::pair<std::string, int>("insert", 4));
		command_codes.insert(std::pair<std::string, int>("exit", 5));
		command_codes.insert(std::pair<std::string, int>("save", 6));
		command_codes.insert(std::pair<std::string, int>("align", 7));
		command_codes.insert(std::pair<std::string, int>("swap", 8));
		command_codes.insert(std::pair<std::string, int>("sort", 9));
		command_codes.insert(std::pair<std::string, int>("clear", 10));
		command_codes.insert(std::pair<std::string, int>("set", 11));
	}

	/** Main Input loop for program Commands */
	void CommandParsing(myTable* Table, std::string const& input);
	/** Returns the Key stored in command_codes map for switching to the given commands function */
	int findCommandForSwitchStatement(std::string const& command);

	/** Vector storing tokenized input */
	std::vector<std::string> splitString(std::vector<std::string> &words, std::string const& input);
	/** Checks, wheter every character is a number in a given string */
	bool isNumber(const std::string& str);
	/** Checks, wheter the range consists of only existing cells */
	bool isValidRangeFormat(const std::string& str);
	/** Stores the given range's corners */
	std::pair<std::string, std::string> getRangeCornerStrings(const std::string& str);
	/** Stores the given range's coordinates as ints */
	std::tuple<int, int, int, int> getRangeCornerInts(const std::string& str);

	/** Input checking for EDIT function */
	void editParsing(myTable* Table, std::string const& input);
	/** Adds N rows or columns */
	void addRowsOrColumns(myTable* Table, std::string const& input);
	/** Deletes N rows or columns */
	void deleteRowsOrColumns(myTable* Table, std::string const& input);
	/** Input checking for INSERT function */
	void insertParsing(myTable* Table, std::string const& input);
	/** Input checking for SAVE function */
	void saveParsing(myTable* Table, std::string const& input);
	/** Input checking for ALIGN function */
	void alignParsing(myTable* Table, std::string const& input);
	/** Input checking for SWAP function */
	void swapParsing(myTable* Table, std::string const& input);
	/** Input checking for SORT function */
	void sortParsing(myTable* Table, std::string const& input);
	/** Input checking for CLEAR function */
	void clearParsing(myTable* Table, std::string const& input);
	/** Input checking for AGGREGATE SET function */
	void setParsing(myTable* Table, std::string const& input);

};

#endif
