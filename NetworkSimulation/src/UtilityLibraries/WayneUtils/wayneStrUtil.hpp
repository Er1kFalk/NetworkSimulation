/*
 * wayneStrUtil.hpp
 *
 *  Created on: 2023年9月26日
 *      Author: weich
 */

#ifndef LIB_WAYNESTRUTIL_HPP_
#define LIB_WAYNESTRUTIL_HPP_

#include <string>
#include <cstring>
#include <algorithm>
#include <regex>

namespace wayne
{
	namespace strUtil
	{
		std::string subStrReplaceAll(const std::string mainStr, const std::string targetSubStr, const std::string replaceToSubStr);
		char* subStrReplaceAll(const char* mainStr, const char* targetSubStr, const char* replaceToSubStr);
		void subStrReplaceAllDirect(std::string* mainStr, const std::string targetSubStr, const std::string replaceToSubStr);
		void subStrReplaceAllDirect(char* &mainStr, const char* targetSubStr, const char* replaceToSubStr);

		std::string subStrReplaceOn(const std::string mainStr, const std::string targetSubStr, const std::string replaceToSubStr, int onOccurance);
		char* subStrReplaceOn(const char* mainStr, const char* targetSubStr, const char* replaceToSubStr, int onOccurance);
		void subStrReplaceOnDirect(std::string* mainStr, const std::string targetSubStr, const std::string replaceToSubStr, int onOccurance);
		void subStrReplaceOnDirect(char* &mainStr, const char* targetSubStr, const char* replaceToSubStr, int onOccurance);

		int subStrOccuranceCount(const char* mainStr, const char* targetSubStr);
		int subStrOccuranceCount(const std::string mainStr, const std::string targetSubStr);
		int subStrOccuranceCount(const std::string* mainStr, const std::string targetSubStr);

		int subStrOccuranceIndex(const std::string mainStr, const std::string targetSubStr, const int thOccurance);
		int subStrOccuranceIndex(const std::string* mainStr, const std::string targetSubStr, const int thOccurance);
		int subStrOccuranceIndex(const char* mainStr, const char* targetSubStr, const int thOccurance);

		std::vector<std::string> splitString(std::string inputString, char splitor);
		std::vector<std::string> splitString(const std::string* inputString, char splitor);
		std::vector<std::string> splitString(std::string* inputString, char splitor);
		std::vector<std::string> splitString(const char* inputString, char splitor);
		std::vector<std::string> splitString(char* inputString, char splitor);

		std::vector<char*> splitCString(std::string inputString, char splitor);
		std::vector<char*> splitCString(const std::string* inputString, char splitor);
		std::vector<char*> splitCString(std::string* inputString, char splitor);
		std::vector<char*> splitCString(const char* inputString, char splitor);
		std::vector<char*> splitCString(char* inputString, char splitor);

		std::string* splitStringStatic(std::string inputString, char splitor);
		std::string* splitStringStatic(const std::string* inputString, char splitor);
		std::string* splitStringStatic(std::string* inputString, char splitor);
		std::string* splitStringStatic(const char* inputString, char splitor);
		std::string* splitStringStatic(char* inputString, char splitor);

		char** splitCStringStatic(std::string inputString, char splitor);
		char** splitCStringStatic(const std::string* inputString, char splitor);
		char** splitCStringStatic(std::string* inputString, char splitor);
		char** splitCStringStatic(const char* inputString, char splitor);
		char** splitCStringStatic(char* inputString, char splitor);

		bool isAsciiString(std::string toCheckString);
		bool isAsciiString(const std::string* toCheckString);
		bool isAsciiString(std::string* toCheckString);
		bool isAsciiString(const char* toCheckString);
		bool isAsciiString(char* toCheckString);

		bool isNumberString(std::string toCheckString, bool isFloat = false);
		bool isNumberString(const std::string* toCheckString, bool isFloat = false);
		bool isNumberString(std::string* toCheckString, bool isFloat = false);
		bool isNumberString(const char* toCheckString, bool isFloat = false);
		bool isNumberString(char* toCheckString, bool isFloat = false);
	}
}



#endif /* LIB_WAYNESTRUTIL_HPP_ */
