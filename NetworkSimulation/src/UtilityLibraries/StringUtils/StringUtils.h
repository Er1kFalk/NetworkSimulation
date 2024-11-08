/*
 * StringUtils.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include <string>
#include <vector>

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

namespace StringUtils {
	std::string to_lower(std::string s);
    bool is_valid_ipv4(std::string ipv4);
	std::vector<unsigned char> string_to_ipv4_address(std::string ipv4);
}

#endif /* STRINGUTILS_H_ */
