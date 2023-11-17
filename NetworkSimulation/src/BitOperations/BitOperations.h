/*
 * BitOperations.h
 *
 *  Created on: 26 Oct 2023
 *      Author: erik
 */

#ifndef BITOPERATIONS_H_
#define BITOPERATIONS_H_

#include <array>
#include <vector>
#include <stdint.h>

namespace BitOperations {
    unsigned char reset_n_upper_bits(unsigned char byte_to_change, unsigned char upper_bit_amount);

    unsigned char set_n_upper_bits(unsigned char byte_to_change, unsigned char value_to_set, unsigned char upper_bit_amount);

    unsigned char read_n_upper_bits (unsigned char byte, unsigned char upper_bit_amount);

    unsigned char reset_n_lower_bits(unsigned char byte_to_change, unsigned char lower_bit_amount);

    unsigned char set_n_lower_bits(unsigned char byte_to_change, unsigned char value_to_set, unsigned char lower_bit_amount);

    unsigned char read_n_lower_bits (unsigned char byte, unsigned char lower_bit_amount);

    unsigned char read_nth_lsb (unsigned char byte, unsigned char n);
    
    unsigned char set_nth_lsb (unsigned char byte, unsigned char n, bool val);

    std::array<unsigned char, 2> int16_to_char_arr (uint16_t n);

    std::array<unsigned char, 4> int32_to_char_arr (uint32_t n);
    
    std::vector<unsigned char> int16_to_char_vector (uint16_t n, std::vector<unsigned char> vec, uint32_t start_index);

    std::vector<unsigned char> int32_to_char_vector (uint16_t n, std::vector<unsigned char> vec, uint32_t start_index);

    uint16_t char_arr_to_int16 (std::array<unsigned char, 2> arr);

    uint32_t char_arr_to_int32 (std::array<unsigned char, 4> arr);

    uint16_t char_vector_to_int16 (std::vector<unsigned char> vec, uint32_t start_index);

    uint32_t char_vector_to_int32 (std::vector<unsigned char> vec, uint32_t start_index);
}

#endif /*BITOPERATIONS_H_*/