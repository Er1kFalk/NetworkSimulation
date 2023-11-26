/*
 * wayneFS.cpp
 *
 *  Created on: 2023年10月3日
 *      Author: weich
 */

#include "wayneFS.hpp"

namespace wayne {
	namespace FS {

		/*Create Directory*/
		bool createDirectory(std::string dirPath, std::string writeType)
		{
			if (isDirectoryExist(dirPath))
			{
				if (writeType == (std::string)"s" || writeType == (std::string)"d")
				{
					return false;
				}
				else if (writeType == (std::string)"o")
				{
					if (removeDirectory(dirPath))
					{
						return std::filesystem::create_directory(dirPath);
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			return std::filesystem::create_directory(dirPath);
		}

		bool createDirectory(const char* dirPath, const char* writeType)
		{
			std::string strDirPath(dirPath);
			std::string strWriteType;
			return createDirectory(strDirPath, strWriteType);
		}

		bool createDirectory(char* dirPath, char* writeType)
		{
			std::string strDirPath(dirPath);
			std::string strWriteType;
			return createDirectory(strDirPath, strWriteType);
		}

		/*Remove Directory*/
		bool removeDirectory(std::string dirPath)
		{
			if (isDirectoryExist(dirPath))
			{
				return std::filesystem::remove_all(dirPath);
			}
			return false;
		}

		bool removeDirectory(const char* dirPath)
		{
			std::string strDirPath(dirPath);
			return removeDirectory(strDirPath);
		}

		bool removeDirectory(char* dirPath)
		{
			std::string strDirPath(dirPath);
			return removeDirectory(strDirPath);
		}

		/*Copy Directory*/

		bool copyDirectory(std::string sourcePath, std::string destPath, std::string writeType)
		{
			if (isDirectoryExist(destPath))
			{
				if (writeType == (std::string)"m")
				{
					std::filesystem::copy(sourcePath, destPath, std::filesystem::copy_options::recursive);
					return true;
				}
				else if (writeType == (std::string)"o")
				{
					std::filesystem::copy(sourcePath, destPath, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
					return true;
				}
				else if (writeType == (std::string)"s" || writeType == (std::string)"d")
				{
					wayne::IO::logLn(destPath + (std::string)" exists!", true);
					return false;
				}
				else
				{
					wayne::IO::logLn((std::string)"Unknown Write Type : " + writeType, true);
					return false;
				}
			}
			std::filesystem::copy(sourcePath, destPath, std::filesystem::copy_options::recursive);
			return true;
		}

		bool copyDirectory(const char* sourcePath, const char* destPath, const char* writeType)
		{
			std::string strSourcePath(sourcePath);
			std::string strDestPath(destPath);
			std::string strWriteType(writeType);
			return copyDirectory(strSourcePath, strDestPath, strWriteType);
		}

		bool copyDirectory(char* sourcePath, char* destPath, char* writeType)
		{
			std::string strSourcePath(sourcePath);
			std::string strDestPath(destPath);
			std::string strWriteType(writeType);
			return copyDirectory(strSourcePath, strDestPath, strWriteType);
		}

		/*Move Directory*/
		bool moveDirectory(std::string sourcePath, std::string destPath, std::string writeType)
		{
			if (isDirectoryExist(destPath))
			{
				if (copyDirectory(sourcePath, destPath, writeType))
				{
					return removeDirectory(sourcePath);
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (writeType == (std::string)"s")
				{
					if (copyDirectory(sourcePath, destPath))
					{
						return removeDirectory(sourcePath);
					}
					else
					{
						return false;
					}
				}
				else
				{
					/*Ignore the writeType, it is only avail when the destPath exists*/
					std::filesystem::rename(sourcePath, destPath);
					return true;
				}
			}
		}

		bool moveDirectory(const char* sourcePath, const char* destPath, const char* writeType)
		{
			std::string strSourcePath(sourcePath);
			std::string strDestPath(destPath);
			std::string strWriteType(writeType);
			return moveDirectory(strSourcePath, strDestPath, strWriteType);
		}

		bool moveDirectory(char* sourcePath, char* destPath, char* writeType)
		{
			std::string strSourcePath(sourcePath);
			std::string strDestPath(destPath);
			std::string strWriteType(writeType);
			return moveDirectory(strSourcePath, strDestPath, strWriteType);
		}

		/*Create File*/
		bool createFile(std::string filePath, std::string writeType)
		{
			if (isFileExist(filePath))
			{
				if (writeType == (std::string)"s" || writeType == (std::string)"d")
				{
					return false;
				}
				else if (writeType == (std::string)"o")
				{
					removeFile(filePath);
					std::ofstream fileOutput(filePath.c_str());
					if (fileOutput.is_open())
					{
						fileOutput.close();
						return true;
					}
					return false;
				}
				else
				{
					wayne::IO::outLn((std::string)"Unsupported Flag : " + writeType);
					return false;
				}
			}
			else
			{
				std::ofstream fileOutput(filePath);
				if (fileOutput.is_open())
				{
					fileOutput.close();
					return true;
				}
				return false;
			}

		}

		bool createFile(const char* filePath, const char* writeType)
		{
			std::string strFilePath(filePath);
			std::string strWriteType(writeType);
			return createFile(strFilePath, strWriteType);
		}

		bool createFile(char* filePath, char* writeType)
		{
			std::string strFilePath(filePath);
			std::string strWriteType(writeType);
			return createFile(strFilePath, strWriteType);
		}

		/*Remove File*/
		bool removeFile(std::string filePath)
		{
			if (isFileExist(filePath))
			{
				return false;
			}
			return std::filesystem::remove(filePath);
		}

		bool removeFile(const char* filePath)
		{
			std::string strFilePath(filePath);
			return removeFile(strFilePath);
		}

		bool removeFile(char* filePath)
		{
			std::string strFilePath(filePath);
			return removeFile(strFilePath);
		}

		/*Copy File*/
		bool copyFile(std::string sourcePath, std::string destPath, std::string writeType)
		{
			if (isFileExist(destPath))
			{
				if (writeType == (std::string)"o")
				{
					std::filesystem::copy(sourcePath, destPath, std::filesystem::copy_options::overwrite_existing);
					return true;
				}
				else if (writeType == (std::string)"s" || writeType == (std::string)"d")
				{
					wayne::IO::logLn(destPath + (std::string)" exists!", true);
					return false;
				}
				else
				{
					wayne::IO::logLn((std::string)"Unknown Write Type : " + writeType, true);
					return false;
				}
			}
			std::filesystem::copy(sourcePath, destPath);
			return true;
		}

		bool copyFile(const char* sourcePath, const char* destPath, const char* writeType)
		{
			std::string strSourcePath(sourcePath);
			std::string strDestPath(destPath);
			std::string strWriteType(writeType);
			return copyFile(strSourcePath, strDestPath, strWriteType);
		}

		bool copyFile(char* sourcePath, char* destPath, char* writeType)
		{
			std::string strSourcePath(sourcePath);
			std::string strDestPath(destPath);
			std::string strWriteType(writeType);
			return copyFile(strSourcePath, strDestPath, strWriteType);
		}

		/*Move File*/
		bool moveFile(std::string sourcePath, std::string destPath, std::string writeType)
		{
			if (isFileExist(destPath))
			{
				if (copyFile(sourcePath, destPath, writeType))
				{
					return removeFile(sourcePath);
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (writeType == (std::string)"s")
				{
					if (copyFile(sourcePath, destPath))
					{
						return removeFile(sourcePath);
					}
					return false;
				}
				else
				{
					std::filesystem::rename(sourcePath, destPath);
					return true;
				}
			}
		}

		bool moveFile(const char* sourcePath, const char* destPath, const char* writeType)
		{
			std::string strSourcePath(sourcePath);
			std::string strDestPath(destPath);
			std::string strWriteType(writeType);
			return moveFile(strSourcePath, strDestPath, strWriteType);
		}

		bool moveFile(char* sourcePath, char* destPath, char* writeType)
		{
			std::string strSourcePath(sourcePath);
			std::string strDestPath(destPath);
			std::string strWriteType(writeType);
			return moveFile(strSourcePath, strDestPath, strWriteType);
		}

		/*Is File Exist*/
		bool isFileExist(std::string filePath)
		{
			return std::filesystem::exists(filePath);
		}

		bool isFileExist(const char* filePath)
		{
			std::string strFilePath(filePath);
			return isFileExist(strFilePath);
		}

		bool isFileExist(char* filePath)
		{
			std::string strFilePath(filePath);
			return isFileExist(strFilePath);
		}

		/*Is The Destination a File*/
		bool isFile(std::string filePath)
		{
			return std::filesystem::is_regular_file(filePath);
		}

		bool isFile(const char* filePath)
		{
			std::string strFilePath(filePath);
			return isFile(strFilePath);
		}

		bool isFile(char* filePath)
		{
			std::string strFilePath(filePath);
			return isFile(strFilePath);
		}

		/*Is Directory Exist*/
		bool isDirectoryExist(std::string dirPath)
		{
			return std::filesystem::exists(dirPath);
		}

		bool isDirectoryExist(const char* dirPath)
		{
			std::string strDirPath(dirPath);
			return isFileExist(strDirPath);
		}

		bool isDirectoryExist(char* dirPath)
		{
			std::string strDirPath(dirPath);
			return isFileExist(strDirPath);
		}

		/*Is The Destination a File*/
		bool isDirectory(std::string dirPath)
		{
			return (std::filesystem::is_directory(dirPath));
		}

		bool isDirectory(const char* dirPath)
		{
			std::string strDirPath(dirPath);
			return isDirectory(strDirPath);
		}

		bool isDirectory(char* dirPath)
		{
			std::string strDirPath(dirPath);
			return isDirectory(strDirPath);
		}

		/*Get the size of a directory*/
		int getDirectorySize(std::string dirPath)
		{
			if (!isDirectory(dirPath))
			{
				return 0;
			}

			int directorySize = 0;
			for (std::filesystem::directory_entry dirEntry : std::filesystem::recursive_directory_iterator(dirPath))
			{
				std::string filePath = dirEntry.path().string();
				isFile(filePath) ? directorySize += getFileSize(filePath) : directorySize += 0;
			}
			return (int) directorySize;
		}

		int getDirectorySize(const char* dirPath)
		{
			std::string strDirPath(dirPath);
			return getDirectorySize(strDirPath);
		}

		int getDirectorySize(char* dirPath)
		{
			std::string strDirPath(dirPath);
			return getDirectorySize(strDirPath);
		}

		/*Get the size of a file*/
		int getFileSize(std::string filePath)
		{
			return (isFile(filePath)) ? (int)std::filesystem::file_size(filePath) : 0;
		}

		int getFileSize(const char* filePath)
		{
			std::string strFilePath(filePath);
			return getFileSize(strFilePath);
		}

		int getFileSize(char* filePath)
		{
			std::string strFilePath(filePath);
			return getFileSize(strFilePath);
		}

		/*Get the list of items in directory*/
		std::vector<std::string> getStringListDir(std::string dirPath)
		{
			std::vector<std::string> fileList;
			if (!isDirectory(dirPath))
			{
				return fileList;
			}
			for (std::filesystem::directory_entry dirEntry : std::filesystem::recursive_directory_iterator(dirPath))
			{
				fileList.push_back(dirEntry.path().string());
			}
			return fileList;
		}

		std::vector<std::string> getStringListDir(const char* dirPath)
		{
			std::string strDirPath(dirPath);
			return getStringListDir(strDirPath);
		}

		std::vector<std::string> getStringListDir(char* dirPath)
		{
			std::string strDirPath(dirPath);
			return getStringListDir(strDirPath);
		}

		std::vector<char*> getCStringListDir(std::string dirPath)
		{
			std::vector<char*> fileList;
			if (!isDirectory(dirPath))
			{
				return fileList;
			}
			for (std::filesystem::directory_entry dirEntry : std::filesystem::recursive_directory_iterator(dirPath))
			{
				char * charDirEntry = new char[dirEntry.path().string().length()];
				std::strncpy(charDirEntry, dirEntry.path().string().c_str(), dirEntry.path().string().length());
				fileList.push_back(charDirEntry);
			}
			return fileList;
		}

		std::vector<char*> getCStringListDir(const char* dirPath)
		{
			std::string strDirPath(dirPath);
			return getCStringListDir(strDirPath);
		}

		std::vector<char*> getCStringListDir(char* dirPath)
		{
			std::string strDirPath(dirPath);
			return getCStringListDir(strDirPath);
		}

		std::string* getStringListDirStatic(std::string dirPath)
		{
			std::vector<std::string> returnedList = getStringListDir(dirPath);
			std::string* toReturn = new std::string[(int)returnedList.size()];
			for (size_t i = 0; i < returnedList.size(); i++)
			{
				toReturn[i] = returnedList[i];
			}
			return toReturn;
		}

		std::string* getStringListDirStatic(const char* dirPath)
		{
			std::string strDirPath(dirPath);
			return getStringListDirStatic(strDirPath);
		}

		std::string* getStringListDirStatic(char* dirPath)
		{
			std::string strDirPath(dirPath);
			return getStringListDirStatic(strDirPath);
		}

		char** getCStringListDirStatic(std::string dirPath)
		{
			std::vector<std::string> returnedList = getStringListDir(dirPath);
			char** toReturn = new char*[returnedList.size()];
			for (size_t i = 0; i < returnedList.size(); i++)
			{
				toReturn[i] = new char[returnedList[i].length()];
				std::strncpy(toReturn[i], returnedList[i].c_str(), returnedList[i].length());
			}
			return toReturn;
		}

		char** getCStringListDirStatic(const char* dirPath)
		{
			std::string strDirPath(dirPath);
			return getCStringListDirStatic(strDirPath);
		}

		char** getCStringListDirStatic(char* dirPath)
		{
			std::string strDirPath(dirPath);
			return getCStringListDirStatic(strDirPath);
		}

		std::vector<std::string> getStringContent(std::string filePath, int amountOfLines, std::string readType)
		{
			std::vector<std::string> fileContent;
			if (!isFileExist(filePath))
			{
				return fileContent;
			}
			std::string readBuffer;
			std::ifstream fileStream(filePath.c_str());
			if (readType.find("a") != std::string::npos || readType.find("d") != std::string::npos)
			{
				while (fileStream)
				{
					std::getline(fileStream, readBuffer);
					fileContent.push_back(readBuffer);
				}
				fileStream.close();
				return fileContent;
			}
			else if (readType.find("lh") != std::string::npos)
			{
				if (wayne::strUtil::splitString(readType, ' ').size() != 2)
				{
					wayne::IO::logLn("Read Type lh cannot operate without number.", true);
					return fileContent;
				}
				int refLine = std::stoi(wayne::strUtil::splitString(readType, ' ')[1]);
				int readCounter = 0;
				while (fileStream)
				{
					std::getline(fileStream, readBuffer);
					if (readCounter >= refLine && readCounter < refLine + amountOfLines)
					{
						fileContent.push_back(readBuffer);
					}
					else if (readCounter >= refLine + amountOfLines) {
						break;
					}
					readCounter++;
				}
				fileStream.close();
				return fileContent;
			}
			else if (readType.find("le") != std::string::npos)
			{
				if (wayne::strUtil::splitString(readType, ' ').size() != 2)
				{
					wayne::IO::logLn("Read Type le cannot operate without number.", true);
					return fileContent;
				}
				int refLine = std::stoi(wayne::strUtil::splitString(readType, ' ')[1]) - amountOfLines;
				int readCounter = 0;
				if (refLine < 0)
				{
					refLine = 0;
				}
				while (fileStream)
				{
					std::getline(fileStream, readBuffer);
					if (readCounter > refLine && readCounter <= std::stoi(wayne::strUtil::splitString(readType, ' ')[1]))
					{
						fileContent.push_back(readBuffer);
					}
					else if (readCounter > std::stoi(wayne::strUtil::splitString(readType, ' ')[1]))
					{
						break;
					}
					readCounter++;
				}
				fileStream.close();
				return fileContent;
			}
			else if (readType.find("h") != std::string::npos)
			{
				int readCounter = 0;
				while (fileStream && readCounter < amountOfLines)
				{
					std::getline(fileStream, readBuffer);
					fileContent.push_back(readBuffer);
					readCounter++;
				}
				fileStream.close();
				return fileContent;
			}
			else if (readType.find("e") != std::string::npos)
			{
				while (fileStream)
				{
					std::getline(fileStream, readBuffer);
					fileContent.push_back(readBuffer);
					if ((int)fileContent.size() > amountOfLines)
					{
						fileContent.erase(fileContent.begin());
					}
				}
				fileStream.close();
				return fileContent;
			}
			else
			{
				fileStream.close();
				return fileContent;
			}
		}

		std::vector<std::string> getStringContent(const char* filePath, int amountOfLines, const char* readType)
		{
			std::string strFilePath(filePath);
			std::string strReadType(readType);
			return getStringContent(strFilePath, amountOfLines, strReadType);
		}

		std::vector<std::string> getStringContent(char* filePath, int amountOfLines, char* readType)
		{
			std::string strFilePath(filePath);
			std::string strReadType(readType);
			return getStringContent(strFilePath, amountOfLines, strReadType);
		}

		std::vector<char*> getCStringContent(std::string filePath, int amountOfLines, std::string readType)
		{
			std::vector<std::string> returnedList = getStringContent(filePath, amountOfLines, readType);
			std::vector<char*> toReturn;
			for (std::string content : returnedList)
			{
				char* charContent = new char[content.length()];
				std::strncpy(charContent, content.c_str(), content.length());
				toReturn.push_back(charContent);
			}
			return toReturn;
		}

		std::vector<char*> getCStringContent(const char* filePath, int amountOfLines, const char* readType)
		{
			std::string strFilePath(filePath);
			std::string strReadType(readType);
			return getCStringContent(strFilePath, amountOfLines, strReadType);
		}

		std::vector<char*> getCStringContent(char* filePath, int amountOfLines, char* readType)
		{
			std::string strFilePath(filePath);
			std::string strReadType(readType);
			return getCStringContent(strFilePath, amountOfLines, strReadType);
		}

		std::vector<char> getByteContent(std::string filePath, int amountOfBytes, std::string readType)
		{
			std::vector<char> fileContent;
			if (!isFileExist(filePath))
			{
				return fileContent;
			}
			std::ifstream fileStream(filePath.c_str());
			if (readType.find("a") != std::string::npos || readType.find("d") != std::string::npos)
			{
				while(fileStream)
				{
					char byte = '\0';
					fileStream.read(&byte, 1);
					fileContent.push_back(byte);
				}
				fileStream.close();
				return fileContent;
			}
			else if (readType.find("bh") != std::string::npos)
			{
				if (wayne::strUtil::splitString(readType, ' ').size() != 2)
				{
					wayne::IO::logLn("Read Type bh cannot operate without number", true);
					return fileContent;
				}
				int refByte = std::stoi(wayne::strUtil::splitString(readType, ' ')[1]);
				int readCounter = 0;
				while (fileStream)
				{
					char byte = '\0';
					fileStream.read(&byte, 1);
					if (readCounter >= refByte && readCounter < refByte + amountOfBytes)
					{
						fileContent.push_back(byte);
					}
					else if (readCounter >= refByte + amountOfBytes)
					{
						break;
					}
					readCounter++;
				}
				fileStream.close();
				return fileContent;
			}
			else if (readType.find("be") != std::string::npos)
			{
				if (wayne::strUtil::splitString(readType, ' ').size() != 2)
				{
					wayne::IO::logLn("Read Type be cannot operate without number", true);
					return fileContent;
				}
				int refByte = std::stoi(wayne::strUtil::splitString(readType, ' ')[1]) - amountOfBytes;
				int readCounter = 0;
				if (refByte < 0)
				{
					refByte = 0;
				}
				while (fileStream)
				{
					char byte = '\0';
					fileStream.read(&byte, 1);
					if (readCounter > refByte && readCounter <= std::stoi(wayne::strUtil::splitString(readType, ' ')[1]))
					{
						fileContent.push_back(byte);
					}
					else if (readCounter > std::stoi(wayne::strUtil::splitString(readType, ' ')[1]))
					{
						break;
					}
					readCounter++;
				}
				fileStream.close();
				return fileContent;
			}
			else if (readType.find("h") != std::string::npos)
			{
				int readCounter = 0;
				while(fileStream && readCounter < amountOfBytes)
				{
					char byte = '\0';
					fileStream.read(&byte, 1);
					fileContent.push_back(byte);
					readCounter++;
				}
				fileStream.close();
				return fileContent;
			}
			else if (readType.find("e") != std::string::npos)
			{
				while (fileStream)
				{
					char byte = '\0';
					fileStream.read(&byte, 1);
					fileContent.push_back(byte);
					if ((int)fileContent.size() > amountOfBytes)
					{
						fileContent.erase(fileContent.begin());
					}
				}
				fileStream.close();
				return fileContent;
			}
			else
			{
				fileStream.close();
				return fileContent;
			}
		}

		std::vector<char> getByteContent(const char* filePath, const char* readType, int amountOfBytes)
		{
			std::string strFilePath(filePath);
			std::string strReadType(readType);
			return getByteContent(strFilePath, amountOfBytes, strReadType);
		}

		std::vector<char> getByteContent(char* filePath, char* readType, int amountOfBytes)
		{
			std::string strFilePath(filePath);
			std::string strReadType(readType);
			return getByteContent(strFilePath, amountOfBytes, strReadType);
		}

		bool writeStringContent(std::string filePath, std::vector<std::string> fileContent, std::string writeType)
		{
			if (isFileExist(filePath))
			{
				if (writeType.find("m") != std::string::npos || writeType.find("d") != std::string::npos)
				{
					removeFile(filePath);
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < fileContent.size(); i++)
					{
						writeStream << fileContent[i] << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else if (writeType.find("a") != std::string::npos)
				{
					std::ofstream writeStream(filePath.c_str(), std::ios::app);
					for (size_t i = 0; i < fileContent.size(); i++)
					{
						writeStream << fileContent[i] << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;

				}
				else if (writeType.find("o") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					int cutbackLine = refLine + (int)fileContent.size();
					std::vector<std::string> origFile = getStringContent(filePath, 0, "d");
					if ((size_t)refLine > origFile.size()) {
						return false;
						/*It's impossible to do that.*/
					}
					if ((size_t)cutbackLine > origFile.size())
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << origFile[i] << std::endl;
						}
						for (size_t i = 0; i < fileContent.size(); i++)
						{
							writeStream << fileContent[i] << std::endl;
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
					else
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << origFile[i] << std::endl;
						}
						for (size_t i = 0; i < fileContent.size(); i++)
						{
							writeStream << fileContent[i] << std::endl;
						}
						for (size_t i = (size_t)cutbackLine; i < origFile.size(); i++)
						{
							writeStream << origFile[i] << std::endl;
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
				}
				else if (writeType.find("i") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					std::vector<std::string> origFile = getStringContent(filePath, 0, "d");
					if ((size_t)refLine > origFile.size()) {
						return false;
						/*It's impossible to do that.*/
					}
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < origFile.size(); i++)
					{
						if (i == (size_t) refLine)
						{
							for (size_t j = 0; j < fileContent.size(); j++)
							{
								writeStream << fileContent[i] << std::endl;
							}
						}
						writeStream << origFile[i] << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (createFile(filePath))
				{
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < fileContent.size(); i++)
					{
						writeStream << fileContent[i] << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				return false;
			}
		}

		bool writeStringContent(const char* filePath, std::vector<std::string> fileContent, const char* writeType)
		{
			std::string strFilePath(filePath);
			std::string strWriteType(writeType);
			return writeStringContent(strFilePath, fileContent, strWriteType);
		}

		bool writeStringContent(char* filePath, std::vector<std::string> fileContent, char* writeType)
		{
			std::string strFilePath(filePath);
			std::string strWriteType(writeType);
			return writeStringContent(strFilePath, fileContent, strWriteType);
		}

		bool writeCStringContent(std::string filePath, std::vector<char*> fileContent, std::string writeType)
		{
			if (isFileExist(filePath))
			{
				if (writeType.find("m") != std::string::npos || writeType.find("d") != std::string::npos)
				{
					removeFile(filePath);
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < fileContent.size(); i++)
					{
						writeStream << *(fileContent[i]) << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else if (writeType.find("a") != std::string::npos)
				{
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < fileContent.size(); i++)
					{
						writeStream << *(fileContent[i]) << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else if (writeType.find("o") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					int cutbackLine = refLine + (int)fileContent.size();
					std::vector<char*> origFile = getCStringContent(filePath, 0, (std::string)"d");
					if ((size_t)refLine > origFile.size())
					{
						return false;
						/* It's impossible to do that. */
					}
					if ((size_t)cutbackLine > origFile.size())
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << *(origFile[i]) << std::endl;
						}
						for (size_t i = 0; i < fileContent.size(); i++)
						{
							writeStream << *(fileContent[i]) << std::endl;
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
					else
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << *(origFile[i]) << std::endl;
						}
						for (size_t i = 0; i < fileContent.size(); i++)
						{
							writeStream << *(fileContent[i]) << std::endl;
						}
						for (size_t i = (size_t)cutbackLine; i < origFile.size(); i++)
						{
							writeStream << *(origFile[i]) << std::endl;
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
				}
				else if (writeType.find("i") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					std::vector<char*> origFile = getCStringContent(filePath, 0, "d");
					if ((size_t)refLine > origFile.size())
					{
						return false;
					}
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < origFile.size(); i++)
					{
						if (i == (size_t) refLine)
						{
							for (size_t j = 0; j < fileContent.size(); j++)
							{
								writeStream << *(fileContent[i]) << std::endl;
							}
						}
						writeStream << *(origFile[i]) << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (createFile(filePath))
				{
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < fileContent.size(); i++)
					{
						writeStream << *(fileContent[i]) << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				return false;
			}
		}

		bool writeCStringContent(const char* filePath, std::vector<char*> fileContent, const char* writeType)
		{
			return writeCStringContent(const_cast<char*>(filePath), fileContent, const_cast<char*>(writeType));
		}

		bool writeCStringContent(char* filePath, std::vector<char*> fileContent, char* writeType)
		{
			std::string strFilePath(filePath);
			std::string strWriteType(writeType);
			return writeCStringContent(strFilePath, fileContent, strWriteType);
		}

		bool writeByteContent(std::string filePath, std::vector<char> fileContent, std::string writeType)
		{
			if (isFileExist(filePath))
			{
				if (writeType.find("m") != std::string::npos || writeType.find("d") != std::string::npos)
				{
					removeFile(filePath);
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < fileContent.size(); i++)
					{
						writeStream << fileContent[i];
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else if (writeType.find("a") != std::string::npos)
				{
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < fileContent.size(); i++)
					{
						writeStream << fileContent[i];
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else if (writeType.find("o") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					int cutbackLine = refLine + (int)fileContent.size();
					std::vector<char> origFile = getByteContent(filePath, 0, "d");
					if ((size_t)refLine > origFile.size())
					{
						return false;
						/* It's impossible to do that. */
					}
					if ((size_t)cutbackLine > origFile.size())
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << origFile[i];
						}
						for (size_t i = 0; i < fileContent.size(); i++)
						{
							writeStream << fileContent[i];
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
					else
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << origFile[i];
						}
						for (size_t i = 0; i < fileContent.size(); i++)
						{
							writeStream << fileContent[i];
						}
						for (size_t i = (size_t)cutbackLine; i < origFile.size(); i++)
						{
							writeStream << origFile[i];
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
				}
				else if (writeType.find("i") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					std::vector<char> origFile = getByteContent(filePath, 0, "d");
					if ((size_t)refLine > origFile.size())
					{
						return false;
					}
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < origFile.size(); i++)
					{
						if (i == (size_t) refLine)
						{
							for (size_t j = 0; j < fileContent.size(); j++)
							{
								writeStream << fileContent[i];
							}
						}
						writeStream << origFile[i];
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (createFile(filePath))
				{
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < fileContent.size(); i++)
					{
						writeStream << fileContent[i];
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				return false;
			}
		}

		bool writeByteContent(const char* filePath, std::vector<char> fileContent, const char* writeType)
		{
			return writeByteContent(const_cast<char*>(filePath), fileContent, const_cast<char*>(writeType));
		}

		bool writeByteContent(char* filePath, std::vector<char> fileContent, char* writeType)
		{
			std::string strFilePath(filePath);
			std::string strWriteType(writeType);
			return writeByteContent(strFilePath, fileContent, strWriteType);
		}

		bool writeStringContentStatic(std::string filePath, std::string* fileContent, int fileLines, std::string writeType)
		{
			if (isFileExist(filePath))
			{
				if (writeType.find("m") != std::string::npos || writeType.find("d") != std::string::npos)
				{
					removeFile(filePath);
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < (size_t)fileLines; i++)
					{
						writeStream << fileContent[i] << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else if (writeType.find("a") != std::string::npos)
				{
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < (size_t)fileLines; i++)
					{
						writeStream << fileContent[i] << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else if (writeType.find("o") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					int cutbackLine = refLine + fileLines;
					std::vector<std::string> origFile = getStringContent(filePath, 0, "d");
					if ((size_t)refLine > origFile.size())
					{
						return false;
						/* It's impossible to do that. */
					}
					if ((size_t)cutbackLine > origFile.size())
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << origFile[i] << std::endl;
						}
						for (size_t i = 0; i < (size_t)fileLines; i++)
						{
							writeStream << fileContent[i] << std::endl;
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
					else
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << origFile[i] << std::endl;
						}
						for (size_t i = 0; i < (size_t)fileLines; i++)
						{
							writeStream << fileContent[i] << std::endl;
						}
						for (size_t i = (size_t)cutbackLine; i < origFile.size(); i++)
						{
							writeStream << origFile[i] << std::endl;
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
				}
				else if (writeType.find("i") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					std::vector<std::string> origFile = getStringContent(filePath, 0, "d");
					if ((size_t)refLine > origFile.size())
					{
						return false;
					}
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < origFile.size(); i++)
					{
						if (i == (size_t) refLine)
						{
							for (size_t j = 0; j < (size_t)fileLines; j++)
							{
								writeStream << fileContent[i] << std::endl;
							}
						}
						writeStream << origFile[i] << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (createFile(filePath))
				{
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < (size_t)fileLines; i++)
					{
						writeStream << fileContent[i] << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				return false;
			}
		}

		bool writeStringContentStatic(const char* filePath, std::string* fileContent, int fileLines, const char* writeType)
		{
			return writeStringContentStatic(const_cast<char*>(filePath), fileContent, fileLines, const_cast<char*>(writeType));
		}

		bool writeStringContentStatic(char* filePath, std::string* fileContent, int fileLines, char* writeType)
		{
			std::string strFilePath(filePath);
			std::string strWriteType(writeType);
			return writeStringContentStatic(strFilePath, fileContent, fileLines, strWriteType);
		}

		bool writeCStringContentStatic(std::string filePath, char** fileContent, int fileLines, std::string writeType)
		{
			if (isFileExist(filePath))
			{
				if (writeType.find("m") != std::string::npos || writeType.find("d") != std::string::npos)
				{
					removeFile(filePath);
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < (size_t)fileLines; i++)
					{
						writeStream << fileContent[i] << std::endl;;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else if (writeType.find("a") != std::string::npos)
				{
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < (size_t)fileLines; i++)
					{
						writeStream << fileContent[i] << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else if (writeType.find("o") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					int cutbackLine = refLine + fileLines;
					std::vector<std::string> origFile = getStringContent(filePath, 0, "d");
					if ((size_t)refLine > origFile.size())
					{
						return false;
						/* It's impossible to do that. */
					}
					if ((size_t)cutbackLine > origFile.size())
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << origFile[i] << std::endl;
						}
						for (size_t i = 0; i < (size_t)fileLines; i++)
						{
							writeStream << fileContent[i] << std::endl;
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
					else
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << origFile[i] << std::endl;
						}
						for (size_t i = 0; i < (size_t)fileLines; i++)
						{
							writeStream << fileContent[i] << std::endl;
						}
						for (size_t i = (size_t)cutbackLine; i < origFile.size(); i++)
						{
							writeStream << origFile[i] << std::endl;
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
				}
				else if (writeType.find("i") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					std::vector<std::string> origFile = getStringContent(filePath, 0, "d");
					if ((size_t)refLine > origFile.size())
					{
						return false;
					}
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < origFile.size(); i++)
					{
						if (i == (size_t) refLine)
						{
							for (size_t j = 0; j < (size_t)fileLines; j++)
							{
								writeStream << fileContent[i] << std::endl;
							}
						}
						writeStream << origFile[i] << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (createFile(filePath))
				{
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < (size_t)fileLines; i++)
					{
						writeStream << fileContent[i] << std::endl;
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				return false;
			}
		}

		bool writeCStringContentStatic(const char* filePath, char** fileContent, int fileLines, const char* writeType)
		{
			return writeCStringContentStatic(const_cast<char*>(filePath), fileContent, fileLines, const_cast<char*>(writeType));
		}

		bool writeCStringContentStatic(char* filePath, char** fileContent, int fileLines, char* writeType)
		{
			std::string strFilePath(filePath);
			std::string strWriteType(writeType);
			return writeCStringContentStatic(strFilePath, fileContent, fileLines, strWriteType);
		}

		bool writeByteContentStatic(std::string filePath, char* fileContent, int fileBytes, std::string writeType)
		{
			if (isFileExist(filePath))
			{
				if (writeType.find("m") != std::string::npos || writeType.find("d") != std::string::npos)
				{
					removeFile(filePath);
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < (size_t)fileBytes; i++)
					{
						writeStream << fileContent[i];
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else if (writeType.find("a") != std::string::npos)
				{
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < (size_t)fileBytes; i++)
					{
						writeStream << fileContent[i];
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else if (writeType.find("o") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					int cutbackLine = refLine + fileBytes;
					std::vector<char> origFile = getByteContent(filePath, 0, (std::string)"d");
					if ((size_t)refLine > origFile.size())
					{
						return false;
						/* It's impossible to do that. */
					}
					if ((size_t)cutbackLine > origFile.size())
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << origFile[i];
						}
						for (size_t i = 0; i < (size_t)fileBytes; i++)
						{
							writeStream << fileContent[i];
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
					else
					{
						std::ofstream writeStream(filePath.c_str());
						for (size_t i = 0; i < (size_t)refLine; i++)
						{
							writeStream << origFile[i];
						}
						for (size_t i = 0; i < (size_t)fileBytes; i++)
						{
							writeStream << fileContent[i];
						}
						for (size_t i = (size_t)cutbackLine; i < origFile.size(); i++)
						{
							writeStream << origFile[i];
						}
						writeStream.flush();
						writeStream.close();
						return true;
					}
				}
				else if (writeType.find("i") != std::string::npos)
				{
					if (wayne::strUtil::splitString(writeType, ' ').size() != 2)
					{
						return false;
					}
					int refLine = std::stoi(wayne::strUtil::splitString(writeType, ' ')[1]);
					std::vector<char> origFile = getByteContent(filePath, 0, "d");
					if ((size_t)refLine > origFile.size())
					{
						return false;
					}
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < origFile.size(); i++)
					{
						if (i == (size_t) refLine)
						{
							for (size_t j = 0; j < (size_t)fileBytes; j++)
							{
								writeStream << fileContent[i];
							}
						}
						writeStream << origFile[i];
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (createFile(filePath))
				{
					std::ofstream writeStream(filePath.c_str());
					for (size_t i = 0; i < (size_t)fileBytes; i++)
					{
						writeStream << fileContent[i];
					}
					writeStream.flush();
					writeStream.close();
					return true;
				}
				return false;
			}
		}

		bool writeByteContentStatic(const char* filePath, char* fileContent, int fileBytes, const char* writeType)
		{
			std::string strFilePath(filePath);
			std::string strWriteType(writeType);
			return writeByteContentStatic(strFilePath, fileContent, fileBytes, strWriteType);
		}

		bool writeByteContentStatic(char* filePath, char* fileContent, int fileBytes, char* writeType)
		{
			std::string strFilePath(filePath);
			std::string strWriteType(writeType);
			return writeByteContentStatic(strFilePath, fileContent, fileBytes, strWriteType);
		}

		bool writeByteContentStatic(std::string filePath, const char* fileContent, int fileBytes, std::string writeType)
		{
			return writeByteContentStatic(filePath, const_cast<char*>(fileContent), fileBytes, writeType);
		}

		bool writeByteContentStatic(const char* filePath, const char* fileContent, int fileBytes, const char* writeType)
		{
			return writeByteContentStatic(filePath, const_cast<char*>(fileContent), fileBytes, writeType);
		}

		bool writeByteContentStatic(char* filePath, const char* fileContent, int fileBytes, char* writeType)
		{
			return writeByteContentStatic(filePath, const_cast<char*>(fileContent), fileBytes, writeType);
		}

	}
} /* namespace wayne */
