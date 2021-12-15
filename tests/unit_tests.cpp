#include "../myTable.h"
#include "../Cell.h"
#include <string>
#include <gtest/gtest.h>

TEST(TableTest, more) {
	Cell cell1("asd1");
	EXPECT_EQ(cell1.getCellData(),"asd1");
        }

TEST(TableTest, more2) {
	Cell cell1("omg");
	EXPECT_EQ(cell1.getCellData(),"omg");
        }

TEST(TableTest, goodNameTest) {
	ptrToTable = new myTable("first");
	EXPECT_EQ(ptrToTable->getName(),"first");
        }


TEST(TableTest, badNameTest) {
	ptrToTable = new myTable("lofasz");
	EXPECT_EQ(ptrToTable->getName(),"first");
        }


int main(int argc, char ** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
