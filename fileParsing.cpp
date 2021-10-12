#include "fileParsing.h"

//		0	   1	   2  3
//	./prog table.csv -sep ,

myTable* fileParsing::fileHandling(char* argv[]) { // STATIKUS F�GGV�NY !!!!!!!
	std::ifstream myfile;
	myTable* newTable = nullptr;

	myfile.open(argv[1]);
	if (myfile.is_open()) {
		std::cout << argv[1] << " exist." << std::endl;
		newTable = createTableFromFile(myfile,';'); // separator by default is ';' 

		myfile.close();
	}
	else
		std::cout << argv[1] << " doesn't exist." << std::endl;

	return newTable;
}

myTable* fileParsing::fileHandling(char* argv[], std::string separator) {		// SOK a function exit point !
	std::cout << "CALLING SEPARATOR FUNCTION" << std::endl;								//			|
	std::string sepCommandFromArgToString = argv[2];	// -sep							//			|
	std::string sepCharFromArgToString = argv[3];		// -sep [c]						//			|
	if (argv[2] != sepCommandFromArgToString) {											//			|
		std::cout << "Invalid Arguments" << std::endl;									//			|
		return nullptr;												//pl itt			//			|	INPUT CHECKING
	}																					//			|
	if (sepCharFromArgToString.size() != 1 ) {											//			|
		std::cout << "Separator must be 1 character " << std::endl;						//			|
		return nullptr;												// meg itt is		//			|
	}																					//			V

	//------------Calling function to PARSE table with given separator------------//
	std::ifstream myfile;
	myTable* newTable = nullptr;

	myfile.open(argv[1]);
	if (myfile.is_open()) {
		std::cout << argv[1] << " exist." << std::endl;
		char separatorStringToChar = separator[0];
		newTable = createTableFromFile(myfile, separatorStringToChar);

		myfile.close();
	}
	else
		std::cout << argv[1] << " doesn't exist." << std::endl;

	return newTable;


	return nullptr;													//ITT k�ne csak lennie 
}

void fileParsing::saveFile(myTable* Table, std::string fileName, std::string separator = ";") {
	//CHECKING IF FILE EXISTS
	std::ifstream fileStream(fileName);
	std::ofstream openFileStream;
	if (fileStream.is_open()) {
		std::cout << "File exists" << std::endl;
		fileStream.close();
		std::cout << "Removing file" << std::endl;
		std::remove(fileName.c_str());
		std::cout << "Creating file with same name" << std::endl;
		openFileStream.open(fileName);
	}
	else {
		std::cout << "File doesnt exist. Creating file: " << fileName << std::endl;
		openFileStream.open(fileName);
	}
	//----WRITING myTable to file----//
	Table->printTableSpecs();
	Table->printTableWin();
		// getCell (x   ,   y) 
		
	/*for (int j = 0; j < Table->getRow()-1; j++) {

	for (int j = 0; j < Table->getRow(); j++) {


		for (int i = 0; i < Table->getColumn(); i++) {
			openFileStream << Table->getCell(i + 1, j + 1);
			if (i < Table->getColumn() - 1)
				openFileStream << ";";
		}
		if(j < Table->getRow()-1)
			openFileStream << std::endl;
	}
	}*/

	for (int j = 0; j < Table->getRow(); j++) {

		int lastElementInRow = 0;
		for (int iter = 0; iter < Table->getColumn(); iter++) {
			if (Table->getCell(iter + 1, j + 1) != "")
				lastElementInRow = iter + 1;
		}
		std::cout << "Last element in this row: " << lastElementInRow << std::endl;

		for (int i = 0; i < lastElementInRow; i++) {
			openFileStream << Table->getCell(i + 1, j + 1);
			if (i < lastElementInRow - 1)
				openFileStream << separator;
		}
		if(j < Table->getRow()-1)
			openFileStream << std::endl;
	}
}


myTable* fileParsing::createTableFromFile(std::ifstream& myfile,char separator) {	// SOK A KIKOMMENTELT PARANCS, AMIK CSAK DEBUGGOL�SHOZ KELLETTEK,
	std::string line;																// EGY DARABIG M�G HAGYD MEG AZOKAT PLS
	std::cout << "CREATING TABLE" << std::endl;
	unsigned int depth = 0;
	unsigned int max_width = 0;
	unsigned int sepCount = 0;

	//GET DEPTH, MAX_WIDTH
	while (!myfile.eof()) {   // !myfile.eof() wont read last line
		std::getline(myfile, line);
		/*if (line == "") {
			//std::cout << "IGNORING EMPTY LINE IN CSV FILE" << std::endl;
			continue;
		}*/
		// GET CURRENT LINE
	   //COUNT SEPARATORS -> GIVES BACK THE ELEMENTS - 1 value
		sepCount = 0;
		for (unsigned int i = 0; i < line.size(); i++) {
			if (line[i] == separator)
				sepCount++;
		}
		if (sepCount > max_width)
			max_width = sepCount;

		depth++;
	}
	max_width++;

	std::cout << "Depth: " << depth << " MAX_WIDTH: " << max_width << std::endl;
	//CREATE TABLE WITH SAME DIMENSIONS AS THE .csv file
	myTable* newTable = new myTable(depth, max_width);
	std::cout << "newTable created: ";
	newTable->printTableSpecs();

	myfile.clear();		// Clearing stream EOF flag
	myfile.seekg(0);	// setting stream iterator at the beginning

	//PUSHING elements into myTable
	int currentRow = 0;
	int rowElementIndex = 0;
	std::cout << "_BEGINNING OF PARSING_" << std::endl;
	while (!myfile.eof()) {   // !myfile.eof() wont read last line
		std::getline(myfile, line);
		/*if (line == "") {
			//std::cout << "IGNORING EMPTY LINE IN CSV FILE" << std::endl;
			continue;
		}*/
		std::cout << "JUMPING LINE" << std::endl;
		rowElementIndex = 0;
		//1 ELEMENT ONLY in current ROW
		if (line.find(separator) == std::string::npos) {
			std::cout << "pushing 1 element" << std::endl;
			if(line == "")
				newTable->setCell(rowElementIndex + 1, currentRow + 1, "");
			else
				newTable->setCell(rowElementIndex + 1, currentRow + 1,line);
		}

		//MORE THAN 1 ELEMENT in current ROW
		else {
			int delimiterPos = 0;
			std::string remainingString = line;

			while (remainingString.find(separator) != std::string::npos) {
				delimiterPos = 0;
				delimiterPos = remainingString.find(separator);
				
				//std::cout << "Pushing element: " << remainingString.substr(0, delimiterPos) << " to pos: " << currentRow + 1 << " " << rowElementIndex + 1 << std::endl;
				newTable->setCell(rowElementIndex + 1, currentRow + 1, (remainingString.substr(0, delimiterPos)));

					rowElementIndex++;
				

				remainingString = remainingString.substr(delimiterPos + 1);
			}
			if ((remainingString.find(separator) == std::string::npos) && (remainingString.size() != 0)) // Pushing last element of original string
				//std::cout << "Pushing LAST element: "<<delimiterPos << "dpos.  " << remainingString.substr(0, delimiterPos) << " to pos: " << currentRow + 1 << " " << rowElementIndex + 1 << std::endl;
			newTable->setCell(rowElementIndex + 1, currentRow + 1, (remainingString));
		}
		currentRow++;
	}
	std::cout << "Pointer inside function: " << newTable << std::endl;
	return newTable;
}


//static myTable& createTableFromFile(std::string file, char separator) {}
