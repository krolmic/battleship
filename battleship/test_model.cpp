#include "gtest/gtest.h"
#include <iostream>

// The fixture for testing class Project1. From google test primer.
class ModelTest : public ::testing::Test
{    
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	ModelTest()
    {
		// You can do set-up work for each test here.
	}

	virtual ~ModelTest() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Project1.
	
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(ModelTest,  JustSomeTest) {
    int expected_value{427};
    int calculated_value{427};
    EXPECT_EQ(expected_value, calculated_value);
    
    EXPECT_TRUE(true);
}

TEST_F(ModelTest,  JustSomeOtherTest) {
    EXPECT_TRUE(true);
}


// }  // namespace - could surround Project1Test in a namespace
