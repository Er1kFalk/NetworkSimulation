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

// finite automata that returns true if IP is valid
bool StringUtils::is_valid_ipv4(std::string ipv4) {
    std::map<std::tuple<int, std::string>, int> trans_function = {
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
    };

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
    vec_ip[i] = std::stoi(ipv4nr);
    assert(i == 3);
    return vec_ip;
}
