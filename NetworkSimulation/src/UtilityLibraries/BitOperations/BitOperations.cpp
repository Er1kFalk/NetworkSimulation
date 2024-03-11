#include "BitOperations.h"
#include <stdexcept>
#include <sstream>
#include <cassert>

/* LCOV_EXCL_START
DESCRIPTION: Sets the upper bits of BYTE_TO_CHANGE to 0. 
The amount of upper bits to set to 0, is given by UPPER_BIT_AMOUNT.
INPUT:
    - BYTE_TO_CHANGE: 
            RANGE: Any value.
    - UPPER_BIT_AMOUNT: 
            RANGE: [0, 8]
OUTPUT:
    - RANGE: Any value.
    - WHAT: The modified BYTE_TO_CHANGE st. the specified upper bits are set to 0. 
    If UPPER_BIT_AMOUNT >8, an exception is thrown.
LCOV_EXCL_STOP LCOV_EXCL_LINE */

unsigned char BitOperations::reset_n_upper_bits(unsigned char byte_to_change, unsigned char upper_bit_amount) {
    if (upper_bit_amount > __CHAR_BIT__) {
        throw std::invalid_argument("upper_bit_amount too large (>8)");
    }
    assert(upper_bit_amount <= __CHAR_BIT__);
    
    return byte_to_change & ~((1<<upper_bit_amount)-1 << (__CHAR_BIT__-upper_bit_amount));
}

/* LCOV_EXCL_START
DESCRIPTION: Sets the upper bits of BYTE_TO_CHANGE to VALUE_TO_SET. 
The amount of upper bits to set, is given by UPPER_BIT_AMOUNT.
EXAMPLE: UPPER_BIT_AMOUNT = 2, BYTE_TO_CHANGE = 0x0F, VALUE_TO_SET=3.
The result is 0xCF (i.e. setting the two msbits = 0b11 = 3).

INPUT:
    - BYTE_TO_CHANGE: 
            RANGE: Any value.
    - VALUE_TO_SET:
            RANGE: Should fit within the range specified by UPPER_BIT_AMOUNT. 
            E.g. if UPPER_BIT_AMOUNT = 2, VALUE_TO_SET can at most be 2^2-1=3.
    - UPPER_BIT_AMOUNT: 
            RANGE: [0, 8]
OUTPUT:
    - RANGE: Any value.
    - WHAT: The modified BYTE_TO_CHANGE st. the specified upper bits are set to VALUE_TO_SET.
    If VALUE_TO_SET > UPPER_BIT_AMOUNT^2-1, an exception is thrown.
    If UPPER_BIT_AMOUNT > 8, an exception is thrown.
LCOV_EXCL_STOP LCOV_EXCL_LINE */

unsigned char BitOperations::set_n_upper_bits(unsigned char byte_to_change, unsigned char value_to_set, unsigned char upper_bit_amount) {
    if (value_to_set > ((1 << upper_bit_amount)-1)) {
        throw std::invalid_argument("value_to_set too large for selected amount of bits");
    }
    assert(value_to_set <= ((1 << upper_bit_amount)-1));

    byte_to_change = reset_n_upper_bits(byte_to_change, upper_bit_amount);
    return byte_to_change | (value_to_set << (__CHAR_BIT__ -upper_bit_amount));
}

/* LCOV_EXCL_START
DESCRIPTION: Reads the msbits of BYTE. 
The amount of msbits to include, is given by UPPER_BIT_AMOUNT

INPUT:
    - BYTE: 
            RANGE: Any value.
    - UPPER_BIT_AMOUNT: 
            RANGE: [0, 8]
OUTPUT:
    - RANGE: Any value.
    - WHAT: The UPPER_BIT_AMOUNT msbits of BYTE.
    Exception is thrown if UPPER_BIT_AMOUNT > 8.
LCOV_EXCL_STOP LCOV_EXCL_LINE */

unsigned char BitOperations::read_n_upper_bits (unsigned char byte, unsigned char upper_bit_amount) {
    if (upper_bit_amount > __CHAR_BIT__) {
        throw std::invalid_argument("at most 8 bits can be read from a char");
    }
    assert(upper_bit_amount <= __CHAR_BIT__);

    return byte >> (__CHAR_BIT__-upper_bit_amount);
}

/* LCOV_EXCL_START
DESCRIPTION: Sets the lower bits of BYTE_TO_CHANGE to 0. 
The amount of upper bits to set to 0, is given by LOWER_BIT_AMOUNT.
INPUT:
    - BYTE_TO_CHANGE: 
            RANGE: Any value.
    - UPPER_BIT_AMOUNT: 
            RANGE: [0, 8]
OUTPUT:
    - RANGE: Any value.
    - WHAT: The modified BYTE_TO_CHANGE st. the specified lower bits are set to 0. 
    If LOWER_BIT_AMOUNT >8, an exception is thrown.
LCOV_EXCL_STOP LCOV_EXCL_LINE */

unsigned char BitOperations::reset_n_lower_bits(unsigned char byte_to_change, unsigned char lower_bit_amount) {
    if (lower_bit_amount > __CHAR_BIT__) {
        throw std::invalid_argument("lower_bit_amount too large (>8)");
    }
    assert(lower_bit_amount <= __CHAR_BIT__);

    return byte_to_change & ~((1<<lower_bit_amount)-1);
}

/* LCOV_EXCL_START
DESCRIPTION: Sets the lower bits of BYTE_TO_CHANGE to VALUE_TO_SET. 
The amount of lower bits to set, is given by LOWER_BIT_AMOUNT.
EXAMPLE: LOWER_BIT_AMOUNT = 2, BYTE_TO_CHANGE = 0xF0, VALUE_TO_SET=3.
The result is 0xF3 (i.e. setting the two lsbits = 0b11 = 3).

INPUT:
    - BYTE_TO_CHANGE: 
            RANGE: Any value.
    - VALUE_TO_SET:
            RANGE: Should fit within the range specified by LOWER_BIT_AMOUNT. 
            E.g. if LOWER_BIT_AMOUNT = 2, VALUE_TO_SET can at most be 2^2-1=3.
    - UPPER_BIT_AMOUNT: 
            RANGE: [0, 8]
OUTPUT:
    - RANGE: Any value.
    - WHAT: The modified BYTE_TO_CHANGE st. the specified lower bits are set to VALUE_TO_SET.
    If VALUE_TO_SET > LOWER_BIT_AMOUNT^2-1, an exception is thrown.
    If LOWER_BIT_AMOUNT > 8, an exception is thrown.
LCOV_EXCL_STOP LCOV_EXCL_LINE */

unsigned char BitOperations::set_n_lower_bits(unsigned char byte_to_change, unsigned char value_to_set, unsigned char lower_bit_amount) {
    if (value_to_set > ((1 << lower_bit_amount)-1)) {
        throw std::invalid_argument("value_to_set too large for selected amount of bits");
    }
    assert(value_to_set <= ((1 << lower_bit_amount)-1));
    byte_to_change = reset_n_lower_bits(byte_to_change, lower_bit_amount);

    return byte_to_change | value_to_set;
}

/* LCOV_EXCL_START
DESCRIPTION: Reads the lsbits of BYTE. 
The amount of lsbits to include, is given by LOWER_BIT_AMOUNT

INPUT:
    - BYTE: 
            RANGE: Any value.
    - LOWER_BIT_AMOUNT: 
            RANGE: [0, 8]
OUTPUT:
    - RANGE: Any value.
    - WHAT: The LOWER_BIT_AMOUNT lsbits of BYTE.
    Exception is thrown if LOWER_BIT_AMOUNT > 8.
LCOV_EXCL_STOP LCOV_EXCL_LINE */
unsigned char BitOperations::read_n_lower_bits (unsigned char byte, unsigned char lower_bit_amount) {
    if (lower_bit_amount > __CHAR_BIT__) {
        throw std::invalid_argument("at most 8 bits can be read from a char");
    }
    assert(lower_bit_amount >= 0 && lower_bit_amount <= __CHAR_BIT__);

    return byte & ((1<<lower_bit_amount)-1);
}

/* LCOV_EXCL_START
DESCRIPTION: Reads the lsbit N of BYTE. 0-indexed (i.e. N=0 will read the lsbit). 

INPUT:
    - BYTE: 
            RANGE: Any value.
    - N: 
            RANGE: [0, 7]
OUTPUT:
    - RANGE: 0 or 1.
    - WHAT: The nth lsbit of BYTE.
LCOV_EXCL_STOP LCOV_EXCL_LINE */

unsigned char BitOperations::read_nth_lsb (unsigned char byte, unsigned char n) {
    if (n >= __CHAR_BIT__) {
        throw std::invalid_argument("cannot read more than 7th lsbit in unsigned char");
    }
    assert(n < __CHAR_BIT__);
    
    unsigned char result = (byte >> n) & 1;

    assert(result == 0 || result == 1);
    return result;
}


/* LCOV_EXCL_START
DESCRIPTION: Sets the lsbit N of BYTE. 0-indexed (i.e. N=0 will set the lsbit). 

INPUT:
    - BYTE: 
            RANGE: Any value.
    - N: 
            RANGE: [0, 7]
OUTPUT:
    - RANGE: Any value
    - WHAT: The value resulting from setting the Nth lsbit of BYTE.
LCOV_EXCL_STOP LCOV_EXCL_LINE */
unsigned char BitOperations::set_nth_lsb (unsigned char byte, unsigned char n, bool val) {
    if (n >= __CHAR_BIT__) {
        throw std::invalid_argument("cannot set more than 7th lsbit in unsigned char");
    }
    assert(n < __CHAR_BIT__);
    
    if (val) {
        return byte | (1 << n);
    } else {
        return byte & ~(1 << n);
    }
}

/* LCOV_EXCL_START
DESCRIPTION: Converts a 16-bit integer to a char array. 

INPUT:
    - N: 
        RANGE: Any value.
OUTPUT:
    - RANGE: Any value
    - WHAT: The array that results from setting the 8 msbits of N to element 0,
    and the 8 lsbits to element 1
LCOV_EXCL_STOP LCOV_EXCL_LINE */
std::array<unsigned char, 2> BitOperations::int16_to_char_arr (uint16_t n) {
    return {(unsigned char) (n >> 8), (unsigned char) n};
}

/* LCOV_EXCL_START
DESCRIPTION: Converts a 32-bit integer to a char array. 

INPUT:
    - N: 
        RANGE: Any value.
OUTPUT:
    - RANGE: Any value
    - WHAT: Like 16-bit version (but for 32-bits)
LCOV_EXCL_STOP LCOV_EXCL_LINE */
std::array<unsigned char, 4> BitOperations::int32_to_char_arr (uint32_t n) {
    return {(unsigned char) (n >> 24), 
            (unsigned char) (n >> 16),
            (unsigned char) (n >> 8),
            (unsigned char) n};
}

/* LCOV_EXCL_START
DESCRIPTION: Converts a 2-element char array to a 16-bit integer. 

INPUT:
    - ARR: 
        RANGE: Any value.
OUTPUT:
    - RANGE: Any value
    - WHAT: The integer resulting from regarding index 0 as the high order bits,
    and index 1 as the low order bits.
LCOV_EXCL_STOP LCOV_EXCL_LINE */
uint16_t BitOperations::char_arr_to_int16 (std::array<unsigned char, 2> arr) {
    return (((int16_t) arr[0]) << 8) +  arr[1];
}


/* LCOV_EXCL_START
DESCRIPTION: Converts a 4-element char array to a 32-bit integer. 

INPUT:
    - ARR: 
        RANGE: Any value.
OUTPUT:
    - RANGE: Any value
    - WHAT: The integer resulting from regarding index 0 as the msbyte,
    and index 3 as the lsbyte.
LCOV_EXCL_STOP LCOV_EXCL_LINE */
uint32_t BitOperations::char_arr_to_int32 (std::array<unsigned char, 4> arr) {
    return (((int32_t) arr[0]) << 24) +  (((int32_t) arr[1]) << 16) + (((int32_t) arr[2]) << 8) + arr[3];
}


/* LCOV_EXCL_START
DESCRIPTION: Puts the 16-bit number N into char vector at START_INDEX and START_INDEX+1.
(msbyte and lsbyte, respectively) 

INPUT:
    - N: 
        RANGE: Any value.
    - VEC:
        RANGE: Any value.
    - START_INDEX:
        RANGE: START_INDEX+1 < length of VEC (otherwise out of bounds)
OUTPUT:
    - RANGE: Any value
    - WHAT: VEC st. element START_INDEX and START_INDEX+1 
    is set to msbyte and lsbyte of N respectively.
LCOV_EXCL_STOP LCOV_EXCL_LINE */
std::vector<unsigned char> BitOperations::int16_into_char_vector (uint16_t n, std::vector<unsigned char> vec, uint32_t start_index) {
    if (start_index+1 >= vec.size()) {
        throw std::invalid_argument("start index too big or vector too small");
    }
    assert (start_index+1 < vec.size());

    vec[start_index] = (unsigned char) (n >> 8);
    vec[start_index+1] = (unsigned char) n;

    return vec;
}


/* LCOV_EXCL_START
DESCRIPTION: Puts the 32-bit number N into char vector at START_INDEX,..., START_INDEX+3
(START_INDEX is set to msbyte and START_INDEX+3 is set to lsbyte)

INPUT:
    - N: 
        RANGE: Any value.
    - VEC:
        RANGE: Any value.
    - START_INDEX:
        RANGE: START_INDEX+3 < length of VEC (otherwise out of bounds)
OUTPUT:
    - RANGE: Any value
    - WHAT: VEC st. element START_INDEX, START_INDEX+1, START_INDEX+2, START_INDEX+3
    is set to msbyte, 2nd msbyte, 2nd lsbyte and lsbyte respectively
LCOV_EXCL_STOP LCOV_EXCL_LINE */
std::vector<unsigned char> BitOperations::int32_into_char_vector (uint32_t n, std::vector<unsigned char> vec, uint32_t start_index) {
    if (start_index+3 >= vec.size()) {
        throw std::invalid_argument("start index too big or vector too small");
    }
    assert (start_index+3 < vec.size());

    vec[start_index] = (unsigned char) (n >> 24);
    vec[start_index+1] = (unsigned char) (n >> 16);
    vec[start_index+2] = (unsigned char) (n >> 8);
    vec[start_index+3] = (unsigned char) n;

    return vec;
}

/* LCOV_EXCL_START
DESCRIPTION: Converts elements at START_INDEX and START_INDEX+1 to a 16-bit integer.

INPUT:
    - VEC:
        RANGE: Any value.
    - START_INDEX:
        RANGE: START_INDEX+1 < length of VEC (otherwise out of bounds)
OUTPUT:
    - RANGE: Any value
    - WHAT: VEC st. element START_INDEX, START_INDEX+1,
    is set to msbyte and lsbyte respectively
LCOV_EXCL_STOP LCOV_EXCL_LINE */
uint16_t BitOperations::char_vector_to_int16 (std::vector<unsigned char> vec, uint32_t start_index) {
    if (start_index+1 >= vec.size()) {
        throw std::invalid_argument("start index too big or vector too small");
    }
    assert(start_index+1 < vec.size());


    return (((int16_t) vec[start_index]) << 8) +  vec[start_index+1];
}

/* LCOV_EXCL_START
DESCRIPTION: Converts elements at START_INDEX, ..., START_INDEX+3 to a 32-bit integer.

INPUT:
    - VEC:
        RANGE: Any value.
    - START_INDEX:
        RANGE: START_INDEX+3 < length of VEC (otherwise out of bounds)
OUTPUT:
    - RANGE: Any value
    - WHAT: VEC st. element START_INDEX, START_INDEX+1, START_INDEX+2, START_INDEX+3
    is set to msbyte, 2nd msbyte, 2nd lsbyte and lsbyte respectively
LCOV_EXCL_STOP LCOV_EXCL_LINE */
uint32_t BitOperations::char_vector_to_int32 (std::vector<unsigned char> vec, uint32_t start_index) {
    if (start_index+3 >= vec.size()) {
        throw std::invalid_argument("start index too big or vector too small");
    }
    assert(start_index+3 < vec.size());


    return (((int32_t) vec[start_index]) << 24) +  (((int32_t) vec[start_index+1]) << 16) + (((int32_t) vec[start_index+2]) << 8) + vec[start_index+3];
}
