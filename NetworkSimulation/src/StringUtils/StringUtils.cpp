/*
 * StringUtils.cpp
 *
 *  Created on: 11 Oct 2023
 *      Author: erik
 */

#include "StringUtils.h"

std::string StringUtils::to_lower(std::string s) {
	std::string to_lower = "";
	for (char c : s) {
		to_lower += std::tolower(c);
	}
	return to_lower;
}

bool StringUtils::is_hex_symbol(char c) {
	bool is_hex_letter = ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F');
	bool is_number = '0' <= c && c <= '9';


	return (is_hex_letter || is_number);
}

// returns true if in s, the char "repeats" after count chars
// example: s="abc:def:ghi", repeats=':', count=3 returns true, whereas if s="abcd:efgh" it would return false
bool StringUtils::char_repeats_in_string(std::string s, char repeats, std::string::size_type count) {
	if (s.length() < count) {
		return false;
	}
	for (std::string::size_type i = count; i < s.length(); i+=count+1) {
		if (s[i] != repeats) {
			return false;
		}
	}
	return true;
}
