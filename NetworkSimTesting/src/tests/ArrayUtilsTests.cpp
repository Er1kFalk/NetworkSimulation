/*
 * ArrayUtilsTests.cpp
 *
 *  Created on: 11 Oct 2023
 *      Author: erik
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ArrayUtils/ArrayUtils.h"
#include "../TestUtils/TestUtils.h"

// testing array of length 3 converts to vector of length 3 with the same elements in the same order
TEST (ArrayUtils, to_vector) {
	const std::string errmsg = "Array did not convert to vector with the same elements in the same order.";
	std::array<unsigned char, 3> array_of_length_3 = {0x12, 0xAB, 0x01}; // Array of length 3
	std::array<unsigned char, 0> empty_array = {}; // Array of length 0
	std::array<std::string, 4> string_array = {"dsa", "fds", "dsan", "def"};
	std::array<std::array<unsigned char, 3>, 3> array_of_arrays = {{
			{0x12, 0x01, 0x03},
			{0x34, 0xAB, 0x22},
			{0x43, 0xCF, 0x4D}}};

	// they have the same size and their elements are the same in the same order
	EXPECT_THAT(ArrayUtils::to_vector(array_of_length_3), testing::ElementsAreArray(array_of_length_3)) << TestUtils::generate_error_msg("ARRAY OF LENGTH 3", errmsg);
	EXPECT_THAT(ArrayUtils::to_vector(empty_array), testing::ElementsAreArray(empty_array)) << TestUtils::generate_error_msg("EMPTY ARRAY", errmsg);
	EXPECT_THAT(ArrayUtils::to_vector(string_array), testing::ElementsAreArray(string_array)) << TestUtils::generate_error_msg("STRING ARRAY", errmsg);
	EXPECT_THAT(ArrayUtils::to_vector(array_of_arrays), testing::ElementsAreArray(array_of_arrays)) << TestUtils::generate_error_msg("ARRAY OF ARRAYS", errmsg);
}


