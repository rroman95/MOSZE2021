#include "myTable.h"
#include "Cell.h"
#include "CommandParsing.h"
#include "fileParsing.h"
#include "gtest/gtest.h"

Test() {
  Commands commands;
	myTable* ptrToTable = new myTable("firstTable");
  
  EXPECT_EQ(ptrToTable->getName(), "firstTable");
  
        }
