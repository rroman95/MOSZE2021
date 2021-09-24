#ifndef COMMANDPARSING_H
#define COMMANDPARSING_H

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include "myTable.h"

//Forward Declaration

std::string InputTokenization(std::string const& input);
int findCommandForSwitchStatement(std::string const& command);
void editParsing(myTable* Table, std::string const& input);
void addRowsOrColumns(myTable* Table, std::string const& input);
void deleteRowsOrColumns(myTable* Table, std::string const& input);
void CommandParsing(myTable* Table, std::string const& input);


#endif