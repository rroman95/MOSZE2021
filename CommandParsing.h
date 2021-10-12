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
	std::map<std::string, int> command_codes;

	Commands() {
		command_codes.insert(std::pair<std::string, int>("edit", 1));
		command_codes.insert(std::pair<std::string, int>("add", 2));
		command_codes.insert(std::pair<std::string, int>("delete", 3));
		command_codes.insert(std::pair<std::string, int>("insert", 4));
		command_codes.insert(std::pair<std::string, int>("exit", 5));
		command_codes.insert(std::pair<std::string, int>("exit\\r\\n", 5));
		command_codes.insert(std::pair<std::string, int>("exit\\n", 5));
		command_codes.insert(std::pair<std::string, int>("save", 6));
	}

	void CommandParsing(myTable* Table, std::string const& input);
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
