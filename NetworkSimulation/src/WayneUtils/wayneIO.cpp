/*
 * wayneIO.cpp
 *
 *  Created on: 2023年9月26日
 *      Author: weich
 */

#include "wayneIO.hpp"

namespace wayne {
	namespace IO {

		/* Wayne :: IO :: log() */

		void log(	/*Function Tested*/
				std::string message,
				bool isError,
				bool revealFuncName,
				bool timestamping,
				std::string funcName)
		{
			const auto now = std::chrono::system_clock::now();
			time_t timeNow = std::chrono::system_clock::to_time_t(now);
			std::string outputLog = "";
			(revealFuncName) ? outputLog += "[" + funcName + "]" : outputLog += "";
			(revealFuncName && timestamping) ? outputLog += "." : outputLog += "";
			std::string timeString(wayne::strUtil::subStrReplaceAll(std::ctime(&timeNow), "\n", ""));
			(timestamping) ? outputLog += "[" + timeString + "] : " : " : ";
			outputLog += message;
			(isError) ? std::cerr << outputLog : std::cout << outputLog;
		}

		void log(
				const std::string* message,
				bool isError,
				bool revealFuncName,
				bool timestamping,
				std::string funcName)
		{
			log(const_cast<std::string*>(message), isError, revealFuncName, timestamping, funcName);
		}

		void log(
			std::string* message,
			bool isError,
			bool revealFuncName,
			bool timestamping,
			std::string funcName)
		{
			log(*message, isError, revealFuncName, timestamping, funcName);
		}

		void log(
			const char* message,
			bool isError,
			bool revealFuncName,
			bool timestamping,
			std::string funcName)
		{
			log(const_cast<char*>(message), isError, revealFuncName, timestamping, funcName);
		}

		void log(
			char* message,
			bool isError,
			bool revealFuncName,
			bool timestamping,
			std::string funcName)
		{
			std::string strMessage(message);
			log(strMessage, isError, revealFuncName, timestamping, funcName);
		}

		void logLn(
				std::string message,
				bool isError,
				bool revealFuncName,
				bool timestamping,
				std::string funcName)
		{
			message = message.append("\n");
			log(message, isError, revealFuncName, timestamping, funcName);
		}

		void logLn(
				const std::string* message,
				bool isError,
				bool revealFuncName,
				bool timestamping,
				std::string funcName)
		{
			logLn(const_cast<std::string*>(message), isError, revealFuncName, timestamping, funcName);
		}

		void logLn(
				std::string* message,
				bool isError,
				bool revealFuncName,
				bool timestamping,
				std::string funcName)
		{
			logLn(*message, isError, revealFuncName, timestamping, funcName);
		}

		void logLn(
				const char* message,
				bool isError,
				bool revealFuncName,
				bool timestamping,
				std::string funcName)
		{
			logLn(const_cast<char*>(message), isError, revealFuncName, timestamping, funcName);
		}

		void logLn(
				char* message,
				bool isError,
				bool revealFuncName,
				bool timestamping,
				std::string funcName)
		{
			std::string strMessage(message);
			logLn(strMessage, isError, revealFuncName, timestamping, funcName);
		}


		/* Wayne :: IO :: out() */
		void out(std::string message)
		{
			std::cout << message;
		}

		void out(const std::string* message)
		{
			out(const_cast<std::string*>(message));
		}

		void out(std::string* message)
		{
			out(*message);
		}

		void out(char* message)
		{
			std::string strMessage(message);
			out(strMessage);
		}

		void out(const char* message)
		{
			out(const_cast<char*>(message));
		}

		void outLn(std::string message)
		{
			out(message);
			std::cout << std::endl;
		}

		void outLn(const std::string* message)
		{
			outLn(const_cast<std::string*>(message));
		}

		void outLn(std::string* message)
		{
			outLn(*message);
		}

		void outLn(char* message)
		{
			std::string strMessage(message);
			outLn(strMessage);
		}

		void outLn(const char* message)
		{
			outLn(const_cast<char*>(message));
		}

		/* Wayne :: IO :: err() */
		void err(std::string message)
		{
			std::cerr << message;
		}

		void err(const std::string* message)
		{
			err(const_cast<std::string*>(message));
		}

		void err(std::string* message)
		{
			err(*message);
		}

		void err(char *message)
		{
			std::string strMessage(message);
			err(strMessage);
		}

		void err(const char* message)
		{
			err(const_cast<char*>(message));
		}

		void errLn(std::string message)
		{
			err(message);
			std::cerr << std::endl;
		}

		void errLn(const std::string* message)
		{
			errLn(const_cast<std::string*>(message));
		}

		void errLn(std::string* message)
		{
			errLn(*message);
		}

		void errLn(char* message)
		{
			std::string strMessage(message);
			errLn(strMessage);
		}

		void errLn(const char* message)
		{
			errLn(const_cast<char*>(message));
		}

		std::string inSafe(std::string expectingDataType, int amountOfLetters, std::string fromOptions, bool isGetline)
		{
			if (isGetline)
			{
				if ((expectingDataType == "string" || expectingDataType == "std::string") || expectingDataType == "char*")
				{
					std::string inputBuffer;
					std::getline(std::cin, inputBuffer);
					if (inputBuffer.empty())
					{
						logLn("User does not enter any data", true);
						return "";
					}
					if (amountOfLetters <= 0)
					{
						if (fromOptions.empty())
						{
							return inputBuffer;
						}
						else
						{
							std::vector<std::string> optionElements = wayne::strUtil::splitString(inputBuffer, ',');
							for (size_t i = 0; i < optionElements.size(); i++)
							{
								if (wayne::strUtil::subStrOccuranceCount(inputBuffer, optionElements[i]) > 0)
								{
									return optionElements[i];
								}
							}
							return ""; /* This means that nothing could be found */
						}
					}
					else
					{
						if (fromOptions.empty())
						{
							return (inputBuffer.length() <= (size_t)amountOfLetters) ? inputBuffer : inputBuffer.substr(0, amountOfLetters);
							/* If no option limitation were given, just cut the string no matter what. */
						}
						else
						{
							if (inputBuffer.length() > (size_t)amountOfLetters)
							{
								inputBuffer = inputBuffer.substr(0, amountOfLetters);
							}
							std::vector<std::string> optionElements = wayne::strUtil::splitString(inputBuffer, ',');
							for (size_t i = 0; i < optionElements.size(); i++)
							{
								if (wayne::strUtil::subStrOccuranceCount(inputBuffer, optionElements[i]) > 0)
								{
									return optionElements[i];
								}
							}
							return ""; /* This means that nothing could be found */
						}
					}
				}
				else
				{
					logLn("When isGetline is set, inSafe can only accept expecting return data type as either std::string or pointer to a char array", true);
					return "";
				}
			}
			else
			{
				std::string inputBuffer = "";
				std::cin >> inputBuffer;
				if (inputBuffer.empty())
				{
					logLn("User does not enter any data", true);
					return "";
				}
				if (expectingDataType == "char")
				{
					if (inputBuffer.length() > 1)
					{
						logLn("Data type \"char\" can only accept 1 character.", true);
						inputBuffer = inputBuffer.substr(0,1);
					}
					if (fromOptions.length() != 0)
					{
						std::vector<std::string> optionElements = wayne::strUtil::splitString(fromOptions, ',');
						for (size_t i = 0; i < optionElements.size(); i++)
						{
							if (inputBuffer == optionElements[i])
							{
								return inputBuffer;
							}
						}
						logLn("No option matched your input", true);
						return "";
					}
					else
					{
						return inputBuffer;
					}
				}
				else if (expectingDataType == "int" || expectingDataType == "long")
				{
					if (inputBuffer.length() >= (size_t)amountOfLetters)
					{
						inputBuffer = inputBuffer.substr(0, amountOfLetters);
					}
					if (wayne::strUtil::isNumberString(inputBuffer))
					{
						if (fromOptions.empty())
						{
							return inputBuffer;
						}
						else
						{
							std::vector<std::string> optionElements = wayne::strUtil::splitString(fromOptions,',');
							for (size_t i = 0; i < optionElements.size(); i++)
							{
								if (optionElements[i].find(inputBuffer) != std::string::npos)
								{
									return optionElements[i];
								}
							}
							logLn("No option matched your input", true);
							return "";
						}
					}
					else
					{
						return "";
					}
				}
				else if (expectingDataType == "float" || expectingDataType == "double")
				{
					if (inputBuffer.length() >= (size_t)amountOfLetters)
					{
						inputBuffer = inputBuffer.substr(0, amountOfLetters);
					}
					if (wayne::strUtil::isNumberString(inputBuffer, true))
					{
						if (fromOptions.empty())
						{
							return inputBuffer;
						}
						else
						{
							std::vector<std::string> optionElements = wayne::strUtil::splitString(fromOptions,',');
							for (size_t i = 0; i < optionElements.size(); i++)
							{
								if (optionElements[i].find(inputBuffer) != std::string::npos)
								{
									return optionElements[i];
								}
							}
							logLn("No option matched your input", true);
							return "";
						}
					}
					else
					{
						return "";
					}
				}
				else if ((expectingDataType == "string" || expectingDataType == "std::string") || expectingDataType == "char*")
				{
					if (inputBuffer.length() >= (size_t)amountOfLetters)
					{
						inputBuffer = inputBuffer.substr(0, amountOfLetters);
					}
					if (fromOptions.empty())
					{
						return inputBuffer;
					}
					else
					{
						std::vector<std::string> optionElements = wayne::strUtil::splitString(fromOptions, ',');
						for (size_t i = 0; i < optionElements.size(); i++)
						{
							if (optionElements[i].find(inputBuffer) != std::string::npos)
							{
								return optionElements[i];
							}
						}
						logLn("No option matched your input", true);
						return "";
					}
				}
				else
				{
					logLn("Unknown data types.", true);
					return "";
				}
			}
		}

		char* inSafe(const char* expectingDataType, int amountOfLetters, const char* fromOptions, bool isGetLine)
		{
			return inSafe(const_cast<char*>(expectingDataType), amountOfLetters, const_cast<char*>(fromOptions), isGetLine);
		}

		char* inSafe(char* expectingDataType, int amountOfLetters, char* fromOptions, bool isGetLine)
		{
			std::string strExpectingDataType(expectingDataType);
			std::string strFromOptions(fromOptions);
			std::string returnedStr = inSafe(strExpectingDataType, amountOfLetters, strFromOptions, isGetLine);
			char* toReturn = new char[returnedStr.length()];
			std::strncpy(toReturn, returnedStr.c_str(), returnedStr.length());
			return toReturn;
		}
	}

} /* namespace wayne */
