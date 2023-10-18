/*
 * MainTester.cpp
 *
 *  Created on: 10 Oct 2023
 *      Author: erik
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tests/StringUtilsTests.h"
#include "tests/ArrayUtilsTests.h"
#include "tests/MACAddressTests.h"
#include "tests/EthertypeTests.h"
#include "tests/EthernetHeaderTests.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
