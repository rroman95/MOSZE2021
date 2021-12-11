#include "myTable.h"
#include "Cell.h"
#include "CommandParsing.h"
#include "fileParsing.h"
#include "gtest/gtest.h"

TET(TableTest, more) {
 	Commands commands;
	myTable* ptrToTable = new myTable("firstTable");
 	EXPECT_EQ(ptrToTable->getName(), "firstTable");
        }

int main(int argc, char ** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
