#include "BitOperations.h"
#include <stdexcept>
#include <sstream>

unsigned char BitOperations::reset_n_upper_bits(unsigned char byte_to_change, unsigned char upper_bit_amount) {
    if (upper_bit_amount > __CHAR_BIT__) {
        throw std::invalid_argument("upper_bit_amount too large (>8)");
    }
    
    return byte_to_change & ~((1<<upper_bit_amount)-1 << (__CHAR_BIT__-upper_bit_amount));
}

unsigned char BitOperations::set_n_upper_bits(unsigned char byte_to_change, unsigned char value_to_set, unsigned char upper_bit_amount) {
    if (value_to_set > ((1 << upper_bit_amount)-1)) {
        throw std::invalid_argument("Value too large for selected amount of bits");
    }
    byte_to_change = reset_n_upper_bits(byte_to_change, upper_bit_amount);
    return byte_to_change | (value_to_set << (__CHAR_BIT__ -upper_bit_amount));
}

unsigned char BitOperations::read_n_upper_bits (unsigned char byte, unsigned char upper_bit_amount) {
    if (upper_bit_amount > __CHAR_BIT__) {
        throw std::invalid_argument("at most 8 bits can be read from a char");
    }
    return byte >> (__CHAR_BIT__-upper_bit_amount);
}

unsigned char BitOperations::reset_n_lower_bits(unsigned char byte_to_change, unsigned char lower_bit_amount) {
    if (lower_bit_amount > __CHAR_BIT__) {
        throw std::invalid_argument("lower_bit_amount too large (>8)");
    }
    return byte_to_change & ~((1<<lower_bit_amount)-1);
}

unsigned char BitOperations::set_n_lower_bits(unsigned char byte_to_change, unsigned char value_to_set, unsigned char lower_bit_amount) {
    if (value_to_set > ((1 << lower_bit_amount)-1)) {
        throw std::invalid_argument("Value too large for selected amount of bits");
    }
    byte_to_change = reset_n_lower_bits(byte_to_change, lower_bit_amount);
    return byte_to_change | value_to_set;
}

unsigned char BitOperations::read_n_lower_bits (unsigned char byte, unsigned char lower_bit_amount) {
    if (lower_bit_amount > __CHAR_BIT__) {
        throw std::invalid_argument("at most 8 bits can be read from a char");
    }
    return byte & ((1<<lower_bit_amount)-1);
}

unsigned char BitOperations::read_nth_lsb (unsigned char byte, unsigned char n) {
    return (byte >> n) & 1;
}

// 0 indexed
unsigned char BitOperations::set_nth_lsb (unsigned char byte, unsigned char n, bool val) {
    if (val) {
        return byte | (1 << n);
    } else {
        return byte & ~(1 << n);
    }
}

std::array<unsigned char, 2> BitOperations::int16_to_char_arr (uint16_t n) {
    return {(unsigned char) (n >> 8), (unsigned char) n};
}

std::array<unsigned char, 4> BitOperations::int32_to_char_arr (uint32_t n) {
    return {(unsigned char) (n >> 24), 
            (unsigned char) (n >> 16),
            (unsigned char) (n >> 8),
            (unsigned char) n};
}

uint16_t BitOperations::char_arr_to_int16 (std::array<unsigned char, 2> arr) {
    return (((int16_t) arr[0]) << 8) +  arr[1];
}

uint32_t BitOperations::char_arr_to_int32 (std::array<unsigned char, 4> arr) {
    return (((int32_t) arr[0]) << 24) +  (((int32_t) arr[1]) << 16) + (((int32_t) arr[2]) << 8) + arr[3];
}

std::vector<unsigned char> BitOperations::int16_to_char_vector (uint16_t n, std::vector<unsigned char> vec, uint32_t start_index) {
    if (start_index+1 >= vec.size()) {
        std::stringstream errmsg;
        errmsg << "int16_to_char_vector: Start index too big or vector too small." << std::endl << "vector size: " << vec.size() << ", index : " << start_index << std::endl;
        throw std::invalid_argument(errmsg.str());
    }

    vec[start_index] = (unsigned char) (n >> 8);
    vec[start_index+1] = (unsigned char) n;

    return vec;
}

std::vector<unsigned char> BitOperations::int32_to_char_vector (uint16_t n, std::vector<unsigned char> vec, uint32_t start_index) {
    if (start_index+3 >= vec.size()) {
        throw std::invalid_argument("int32_to_char_vector: Start index too big or vector too small");
    }

    vec[start_index] = (unsigned char) (n >> 24);
    vec[start_index+1] = (unsigned char) (n >> 16);
    vec[start_index+2] = (unsigned char) (n >> 8);
    vec[start_index+3] = (unsigned char) n;

    return vec;
}

uint16_t BitOperations::char_vector_to_int16 (std::vector<unsigned char> vec, uint32_t start_index) {
    if (start_index+1 >= vec.size()) {
        throw std::invalid_argument("char_vector_to_int16: Start index too big or vector too small");
    }

    return (((int16_t) vec[start_index]) << 8) +  vec[start_index+1];
}

uint32_t BitOperations::char_vector_to_int32 (std::vector<unsigned char> vec, uint32_t start_index) {
    if (start_index+3 >= vec.size()) {
        throw std::invalid_argument("char_vector_to_int32: Start index too big or vector too small");
    }

    return (((int32_t) vec[start_index]) << 24) +  (((int32_t) vec[start_index+1]) << 16) + (((int32_t) vec[start_index+2]) << 8) + vec[start_index+3];
}