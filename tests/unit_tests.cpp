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

TEST(CellTest, isAggregate) {
	Commands commands;
	myTable* ptrToTable = new myTable("initTable");
	commands.CommandParsing(ptrToTable, "edit a1 =SUM(a2:c2)");
	ASSERT_EQ(ptrToTable->getCellObject(0,0)->printCellData(), "#NAME?");
	EXPECT_EQ(ptrToTable->checkIfCellIsAggregate(0,0), 1);
        }

TEST(TableTest, TableNameTest) {
	myTable* ptrToTable = new myTable("first");
	EXPECT_EQ(ptrToTable->getName(),"first");
        }


TEST(TableTest, dimensionTest) {
	myTable* ptrToTable = new myTable("first");
	EXPECT_EQ(ptrToTable->getRow(),1);
	EXPECT_EQ(ptrToTable->getColumn(),1);
        }

TEST(TableTest, dimensionTest2) {
	myTable* ptrToTable = nullptr;
	ptrToTable = new myTable("first");
	ptrToTable->addRows(5);
	ptrToTable->addColumns(5);
	EXPECT_EQ(ptrToTable->getRow()*ptrToTable->getColumn(),36);
        }


int main(int argc, char ** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
