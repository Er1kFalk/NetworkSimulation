/*
 * TestUtils.cpp
 *
 *  Created on: 11 Oct 2023
 *      Author: erik
 */

#include "TestUtils.h"
#include <iostream>

std::string TestUtils::generate_error_msg(std::string test_name, std::string error_msg) {
	std::string final_msg = "";
	final_msg.append("IN TEST: ");
	final_msg.append(test_name);
	final_msg.append("\n");
	final_msg.append(error_msg);
	return final_msg;
}


