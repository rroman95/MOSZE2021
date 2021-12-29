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
	ASSERT_EQ(ptrToTable->checkIfCellIsAggregate(0,0), 1);
	EXPECT_EQ(ptrToTable->getCellObject(0,0)->data, "=SUM(a2:c2)");
	EXPECT_EQ(ptrToTable->getCellObject(0,0)->getCellData(), "#NAME?");
        }

TEST(CellTest, promoteAndDemoteCell) {
	Commands commands;
	myTable* ptrToTable = new myTable("initTable");
	ASSERT_EQ(ptrToTable->checkIfCellIsAggregate(0,0),0);
	commands.CommandParsing(ptrToTable, "edit a1 =SUM(a2:c2)");
	ASSERT_EQ(ptrToTable->checkIfCellIsAggregate(0,0), 1);
	commands.CommandParsing(ptrToTable, "edit a1 asd");
	ASSERT_EQ(ptrToTable->checkIfCellIsAggregate(0,0), 0);
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

TEST(CommandsTest, editTest) {
	Commands commands;
	myTable* ptrToTable = new myTable("init");
	commands.CommandParsing(ptrToTable, "edit a1 lorem ipsum");
	EXPECT_EQ(ptrToTable->getCellObject(0,0)->getCellData(),"lorem ipsum");
        }

TEST(CommandsTest, alignTest) {
	Commands commands;
	myTable* ptrToTable = new myTable("init");
	commands.CommandParsing(ptrToTable, "align a1 left");
	EXPECT_EQ(ptrToTable->getCellObject(0,0)->getCellAlignment(),'l');
        }

TEST(CommandsTest, swapTest) {
	Commands commands;
	myTable* ptrToTable = new myTable("init");
	commands.CommandParsing(ptrToTable, "add 1 rows");
	commands.CommandParsing(ptrToTable, "edit a1 asd");
	commands.CommandParsing(ptrToTable, "edit a2 lol");
	commands.CommandParsing(ptrToTable, "swap a1 a2");
	EXPECT_EQ(ptrToTable->getCellObject(0,0)->getCellData(),"lol");
	EXPECT_EQ(ptrToTable->getCellObject(0,1)->getCellData(),"asd");
        }

TEST(fileParsingTest, Open_File_And_Check_Dimensions) {
	myTable* ptrToTable = fileParsing::fileHandling("tests/testfile2.csv");
	EXPECT_EQ(ptrToTable->getRow(),3);
	EXPECT_EQ(ptrToTable->getColumn(),3);
        }


int main(int argc, char ** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
