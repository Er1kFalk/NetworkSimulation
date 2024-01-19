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

TEST (StringUtils, is_hex_symbol) {
	std::vector<char> accepted_values = {'a', 'b', 'c', 'd', 'e', 'f', // hex values
			'A', 'B', 'C', 'D', 'E', 'F',
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for (char c : accepted_values) {
		EXPECT_TRUE(StringUtils::is_hex_symbol(c)) << TestUtils::generate_error_msg(std::string("HEX VALUE: ") + c, "Passed a hex value, but function told us that it wasn't a hex value.");
	}

	std::vector<char> some_other_values = {'g', '^', 'k', '+', 'z', 'I'};

	for (char c : some_other_values) {
		EXPECT_FALSE(StringUtils::is_hex_symbol(c)) << TestUtils::generate_error_msg(std::string("NON HEX VALUE: ") + c, "Passed a NON hex value, but function told us that it WAS a hex value.");
	}
}

// tests if char_repeats_in_string on the strings given by tests (helper function for below test)
// does_repeat specifies the char that repeats in the tests, and repeat_freq specifies the frequency of repetitions
// does_not_repeat specifies a char that does not repeat
void char_repeats_in_string_helper_tester(std::string testname, std::vector<std::string> tests, char does_repeat, int repeat_freq, char does_not_repeat) {
	for (std::string s : tests) {
		EXPECT_TRUE(StringUtils::char_repeats_in_string(s, does_repeat, repeat_freq)) << TestUtils::generate_error_msg(testname, "");
		EXPECT_FALSE(StringUtils::char_repeats_in_string(s, does_repeat, repeat_freq+1)) << TestUtils::generate_error_msg(testname, "");
		EXPECT_FALSE(StringUtils::char_repeats_in_string(s, does_repeat, repeat_freq-1)) << TestUtils::generate_error_msg(testname, "");
		EXPECT_FALSE(StringUtils::char_repeats_in_string(s, does_not_repeat, repeat_freq)) << TestUtils::generate_error_msg(testname, "");
	}
}

TEST (StringUtils, char_repeats_in_string_1) {
	// for strings seperated by : every 2 chars
	std::vector<std::string> colon_2_char_sep = {
			"ff:ff:ff:ff",
			"23:as:gf:ds",
			"ss:34:ff:ff"
	};

	// check that it also works for strings separted by > 2 chars
	std::vector<std::string> colon_5_char_sep = {
			"fffff:fffff:fffff:fffff",
			"2321d:asda3:gfdsa:ds23a",
			"ssfds:34sdf:fffff:ff32d"
	};

	// check that it works for other seperators
	std::vector<std::string> dot_5_char_sep = {
			"fffff.fffff.fffff.fffff",
			"2321d.asda3.gfdsa.ds23a",
			"ssfds.34sdf.fffff.ff32d"
	};

	char_repeats_in_string_helper_tester("STRING WITH COLON EVERY 2 CHARS", colon_2_char_sep, ':', 2, '4');
	char_repeats_in_string_helper_tester("STRING WITH COLON EVERY 5 CHARS", colon_5_char_sep, ':', 5, 'g');
	char_repeats_in_string_helper_tester("STRING WITH DOT EVERY 5 CHARS", colon_5_char_sep, ':', 5, 'l');

}

