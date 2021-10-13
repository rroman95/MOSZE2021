#ifndef COMMANDPARSING_H
#define COMMANDPARSING_H

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include "myTable.h"
#include "fileParsing.h"

class Commands {
public:
	std::map<int, std::string> command_codes;

	Commands() {
		command_codes.insert(std::pair<int, std::string>(1, "edit"));
		command_codes.insert(std::pair<int, std::string>(2, "add"));
		command_codes.insert(std::pair<int, std::string>(3, "delete"));
		command_codes.insert(std::pair<int, std::string>(4, "insert"));
		command_codes.insert(std::pair<int, std::string>(5, "exit"));
		command_codes.insert(std::pair<int, std::string>(6, "save"));
	}

	void CommandParsing(myTable* Table, std::string const& input, bool &exitFlag);
	int findCommandForSwitchStatement(std::string const& command);

	std::vector<std::string> splitString(std::vector<std::string> &words, std::string const& input);
	bool isNumber(const std::string& str);

	void editParsing(myTable* Table, std::string const& input);
	void addRowsOrColumns(myTable* Table, std::string const& input);
	void deleteRowsOrColumns(myTable* Table, std::string const& input);
	void insertParsing(myTable* Table, std::string const& input);
	void saveParsing(myTable* Table, std::string const& input);

};

#endif
