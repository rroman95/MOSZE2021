#ifndef COMMANDPARSING_H
#define COMMANDPARSING_H

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include "myTable.h"

//DEFINITIONS

class Commands {
public:
	std::map<std::string, int> command_codes;		// should be private w/ a getter function, but yolo

	Commands() {
		command_codes.insert(std::pair<std::string, int>("edit", 1));
		command_codes.insert(std::pair<std::string, int>("delete", 3));
		command_codes.insert(std::pair<std::string, int>("insert", 4));
		command_codes.insert(std::pair<std::string, int>("exit", 5));
		command_codes.insert(std::pair<std::string, int>("add", 7));
	}
};

std::string InputTokenization(std::string const& input);
int findCommandForSwitchStatement(std::string const& command);
void editParsing(myTable* Table, std::string const& input);
void addRowsOrColumns(myTable* Table, std::string const& input);
void deleteRowsOrColumns(myTable* Table, std::string const& input);
void CommandParsing(myTable* Table, std::string const& input);


#endif
