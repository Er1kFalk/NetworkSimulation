/*
 * StringUtils.cpp
 *
 *  Created on: 11 Oct 2023
 *      Author: erik
 */

#include "StringUtils.h"
#include <stdexcept>
#include <assert.h>
#include <map>

std::string StringUtils::to_lower(std::string s) {
    std::string to_lower = "";
    for (char c : s) {
        to_lower += std::tolower(c);
    }
    return to_lower;
}

// finite automata that returns true if IP is valid
bool StringUtils::is_valid_ipv4(std::string ipv4) {
    const std::map<std::tuple<int, std::string>, int> trans_function = {// LCOV_EXCL_START

        {{0, "nr"}, 1},
        {{1, "nr"}, 2},
        {{2, "nr"}, 3},
        {{1, "."}, 4},
        {{2, "."}, 4},
        {{3, "."}, 4},
        {{5, "nr"}, 6},
        {{6, "nr"}, 7},
        {{7, "nr"}, 8},
        {{6, "nr"}, 6},
    }; // LCOV_EXCL_STOP

    int state = 0;
    int count = 0;
    for (char c : ipv4) {
        std::string action = "";
        if (state == 4) {
            if (count < 3) {
                state = 0;
            } else {
                state = 5;
            }
        }
        if (c>=48 && c <=57) {
            action = "nr";
        }
        else {
            action = c;
        }
        if (auto f = trans_function.find({state, action}); f != trans_function.end()) {
            state = trans_function.at({state, action});
            if (action.compare(".") == 0) {
                count++;
            }
        } else {
            state = -1;
        }
    }
    return state == 6 || state == 7 || state == 8;
}

std::vector<unsigned char> StringUtils::string_to_ipv4_address(std::string ipv4) {
    bool is_valid = StringUtils::is_valid_ipv4(ipv4);
    if (!is_valid) {
        throw std::invalid_argument("You did not provide a valid IPv4 address");
    }
    assert(is_valid);

    std::string ipv4nr = "";
    std::vector<unsigned char> vec_ip = {0, 0, 0, 0};
    assert(vec_ip.size() == 4);

    int i = 0;
    for (unsigned char c : ipv4) {
        if (c>=48 && c <=57) { // c is a nr
            ipv4nr += c;
            assert(ipv4nr.length() <= 3);
        } else { // c is a .
            vec_ip[i] = std::stoi(ipv4nr);
            i++;
            ipv4nr = "";
        }
    }
    vec_ip[i] = std::stoi(ipv4nr);
    assert(i == 3);
    return vec_ip;
}
