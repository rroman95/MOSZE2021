#ifndef FILEPARSING_H
#define FILEPARSING_H
#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>

#include "myTable.h"

struct fileParsing {
	std::string inputFile;

	/** Checks if the given file exists, if no creates it, if yes, overwrites it */
	static myTable* fileHandling(char* argv[]);
	/** Checks if the given file exists, if no creates it, if yes, overwrites it. The string sep is looking for the specified separator in the .csv file */
	static myTable* fileHandling(char* argv[], std::string sep);

	/** Creates a table from a file */
	static myTable* createTableFromFile(std::ifstream&, char _separator);

	/** Saves active myTable to a .csv file */
	static void saveFile(myTable* Table, std::string fileName, std::string separator);
};

#endif
