#ifndef FILEPARSING_H
#define FILEPARSING_H
#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>

#include "myTable.h"

//		0	   1	   2  3
//	./prog table.csv -sep ,

struct fileParsing {
	std::string inputFile;

	//static myTable* fileHandling(char* fileToParse);
	static myTable* fileHandling(char* argv[]);
	static myTable* fileHandling(char* argv[], std::string sep);

	static myTable* createTableFromFile(std::ifstream&, char _separator);

	static void saveFile(myTable* Table, std::string fileName, std::string separator);
};

#endif