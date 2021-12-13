#include "../myTable.h"
//#include "../myTable.cpp"
#include "../Cell.h"
//#include "../Cell.cpp"
#include <string>
#include "gtest/gtest.h"

TEST(TableTest, more) {
	Cell cell1("asd");
	EXPECT_EQ(cell1.getCellData(),"asd1");
        }

int main(int argc, char ** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
