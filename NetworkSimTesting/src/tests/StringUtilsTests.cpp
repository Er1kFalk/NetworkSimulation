#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../NetworkSimulation/src/UtilityLibraries/StringUtils/StringUtils.h"
#include <string>
#include <vector>
#include "../TestUtils/TestUtils.h"

TEST (StringUtils, to_lower) {
	const std::string errmsg = "Function did not convert all letters to lowercase";

	std::string all_upper_case = "ABCD";
	std::string lower = StringUtils::to_lower(all_upper_case);

	EXPECT_THAT(lower, testing::StrEq("abcd")) << TestUtils::generate_error_msg("ALL UPPER CASE", errmsg);

	std::string mixed = "kJhI980";
	lower = StringUtils::to_lower(mixed);
	EXPECT_THAT(lower, testing::StrEq("kjhi980")) << TestUtils::generate_error_msg("MIXED STRING", errmsg);

	std::string all_lower_case = "dsjakl";
	lower = StringUtils::to_lower(all_lower_case);
	EXPECT_THAT(lower, testing::StrEq(all_lower_case)) << TestUtils::generate_error_msg("ALL LOWER CASE", errmsg);;
}

TEST (StringUtils, is_valid_ipv4_WhereIPIsTooLong) {
    std::string test = "192.168.111.1111";
    EXPECT_FALSE(StringUtils::is_valid_ipv4(test));
}

TEST (StringUtils, is_valid_ipv4_WhereAddressHasTooManyDots) {
    std::string test = "192.168.1.1.1";
    EXPECT_FALSE(StringUtils::is_valid_ipv4(test));
}

TEST (StringUtils, is_valid_ipv4_WhereAddressHasLetters) {
    std::string test = "192.16a.1.1";
    EXPECT_FALSE(StringUtils::is_valid_ipv4(test));
}

TEST (StringUtils, is_valid_ipv4_WhereAddressHasMoreThan3NumbersBetweenDots) {
    std::string test = "127.0.1111.1";
    EXPECT_FALSE(StringUtils::is_valid_ipv4(test));
}

TEST (StringUtils, is_valid_ipv4_WhereAddressIsValid) {
    std::string test1 = "192.168.1.1";
    std::string test2 = "127.0.0.1";
    std::string test3 = "1.111.0.111";
    std::string test4 = "111.444.555.666";

    EXPECT_TRUE(StringUtils::is_valid_ipv4(test1));
    EXPECT_TRUE(StringUtils::is_valid_ipv4(test2));
    EXPECT_TRUE(StringUtils::is_valid_ipv4(test3));
    EXPECT_TRUE(StringUtils::is_valid_ipv4(test4));
}

TEST (StringUtils, string_to_ipv4_addressWhereAddressIsValid) {
    std::string test1 = "192.168.1.1";
    std::string test2 = "127.0.0.1";
    std::string test3 = "1.111.0.111";
    std::string test4 = "111.444.555.666";

    EXPECT_THAT(StringUtils::string_to_ipv4_address(test1), testing::ElementsAreArray({192, 168, 1, 1}));
    EXPECT_THAT(StringUtils::string_to_ipv4_address(test2), testing::ElementsAreArray({127, 0, 0, 1}));
    EXPECT_THAT(StringUtils::string_to_ipv4_address(test3), testing::ElementsAreArray({1, 111, 0, 111}));
    EXPECT_THAT(StringUtils::string_to_ipv4_address(test4), testing::ElementsAreArray({111, 444, 555, 666}));
}

TEST (StringUtils, string_to_ipv4_addressWhereAddressIsInValid) {
    std::string test1 = "192.1684.2.1";

    try {
        StringUtils::string_to_ipv4_address(test1);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "You did not provide a valid IPv4 address");
    }
}

