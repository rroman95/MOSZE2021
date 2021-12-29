#include "../myTable.h"
#include "../Cell.h"
#include "../CommandParsing.h"
#include "../fileParsing.h"
#include <string>
#include <gtest/gtest.h>

TEST(CellTest, getCellData) {
	Cell cell1("asd1");
	EXPECT_EQ(cell1.getCellData(),"asd1");
        }

TEST(CellTest, getCellInitialAlignment) {
	Cell cell1("omg");
	EXPECT_EQ(cell1.getCellAlignment(),'r');
        }

TEST(TableTest, TableNameTest) {
	myTable* ptrToTable = nullptr;
	ptrToTable = new myTable("first");
	EXPECT_EQ(ptrToTable->getName(),"first");
        }


TEST(TableTest, dimensionTest) {
	myTable* ptrToTable = nullptr;
	ptrToTable = new myTable("first");
	EXPECT_EQ(ptrToTable->getRow(),1);
	EXPECT_EQ(ptrToTable->getColumn(),1);
        }


int main(int argc, char ** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
