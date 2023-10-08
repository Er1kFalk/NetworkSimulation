/*
 * StringUtils.cpp
 *
 *  Created on: 8 Oct 2023
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
