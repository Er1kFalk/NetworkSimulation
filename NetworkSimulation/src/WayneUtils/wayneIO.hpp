/*
 * wayneIO.h
 *
 *  Created on: 2023年9月26日
 *      Author: weich
 */

#ifndef LIB_WAYNEIO_HPP_
#define LIB_WAYNEIO_HPP_
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "wayneStrUtil.hpp"

namespace wayne {
	namespace IO {

		void log(
				std::string message,
				bool isError = false,
				bool revealFuncName = true,
				bool timestamping = true,
				std::string funcName = __builtin_FUNCTION());

		void log(
				const std::string* message,
				bool isError = false,
				bool revealFuncName = true,
				bool timestamping = true,
				std::string funcName = __builtin_FUNCTION());

		void log(
				std::string* message,
				bool isError = false,
				bool revealFuncName = true,
				bool timestamping = true,
				std::string funcName = __builtin_FUNCTION());

		void log(
				const char* message,
				bool isError = false,
				bool revealFuncName = true,
				bool timestamping = true,
				std::string funcName = __builtin_FUNCTION());

		void log(
				char* message,
				bool isError = false,
				bool revealFuncName = true,
				bool timestamping = true,
				std::string funcName = __builtin_FUNCTION());

		void logLn(
				std::string message,
				bool isError = false,
				bool revealFuncName = true,
				bool timestamping = true,
				std::string funcName = __builtin_FUNCTION());

		void logLn(
				std::string* message,
				bool isError = false,
				bool revealFuncName = true,
				bool timestamping = true,
				std::string funcName = __builtin_FUNCTION());

		void logLn(
				const char* message,
				bool isError = false,
				bool revealFuncName = true,
				bool timestamping = true,
				std::string funcName = __builtin_FUNCTION());

		void logLn(
				char* message,
				bool isError = false,
				bool revealFuncName = true,
				bool timestamping = true,
				std::string funcName = __builtin_FUNCTION());

		void out(std::string message);
		void out(const std::string* message);
		void out(std::string* message);
		void out(char* message);
		void out(const char* message);

		void outLn(std::string message);
		void outLn(const std::string* message);
		void outLn(std::string* message);
		void outLn(char* message);
		void outLn(const char* message);

		void err(std::string message);
		void err(const std::string* message);
		void err(std::string* message);
		void err(char *message);
		void err(const char* message);

		void errLn(std::string message);
		void errLn(const std::string* message);
		void errLn(std::string* message);
		void errLn(char* message);
		void errLn(const char* message);

		std::string inSafe(std::string expectingDataType, int amountOfLetters, std::string fromOptions, bool isGetline = true);
		char* inSafe(const char* expectingDataType, int amountOfLetters, const char* fromOptions, bool isGetLine = true);
		char* inSafe(char* expectingDataType, int amountOfLetters, char* fromOptions, bool isGetLine = true);
	}
} /* namespace wayne */

#endif /* LIB_WAYNEIO_HPP_ */
