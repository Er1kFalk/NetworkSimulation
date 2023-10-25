/*
 * StringUtils.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include <string>

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

namespace StringUtils {
	std::string to_lower(std::string s);
	bool is_hex_symbol(char c);
	bool char_repeats_in_string(std::string s, char repeats, std::string::size_type count);
}

#endif /* STRINGUTILS_H_ */
