/*
 * UnitTest.cpp
 *
 *  Created on: 24 Sept 2023
 *      Author: erik
 */


#include <gtest/gtest.h>

TEST(MyTest, MyTest1) {
	EXPECT_EQ(10*2, 20);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
