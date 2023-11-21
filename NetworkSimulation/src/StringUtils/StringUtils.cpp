/*
 * StringUtils.cpp
 *
 *  Created on: 11 Oct 2023
 *      Author: erik
 */

#include "StringUtils.h"
#include <stdexcept>
#include <assert.h>

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


std::vector<unsigned char> StringUtils::string_to_ipv4_address(std::string ipv4) {
	const int max_len = 15; // IP can at most be 15 long (3 dots + 3*4 numbers)

	if (ipv4.length() > max_len) {
		throw std::invalid_argument("IPv4 address can at most have length 15");
	}
	assert(ipv4.length() <= max_len);

	std::string ipv4nr = "";
	std::vector<unsigned char> vec_ip = {0, 0, 0, 0};
	assert(vec_ip.size() == 4);

	int i = 0;
	for (unsigned char c : ipv4) {
		if (c>=48 && c <=57) { // c is a nr
			ipv4nr += c;
			assert(ipv4nr.length() <= 3);
		} else if (c == '.') {
			vec_ip[i] = std::stoi(ipv4nr);
			i++;
			ipv4nr = "";
			continue;
		} else {
			throw std::invalid_argument("Not a valid ip: may only conbtain . and numbers");
		}
	}
	assert(i == 3);
	return vec_ip;
}
