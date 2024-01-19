#include "BitOperationsTests.h"
#include "../../../NetworkSimulation/src/UtilityLibraries/BitOperations/BitOperations.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>


/* 
reset_n_upper_bits()
 */ 

TEST(BitOperations, reset4UpperBits) {
    char test = 0xFF;
    EXPECT_EQ(BitOperations::reset_n_upper_bits(test, 4), 0xF);
}

TEST(BitOperations, reset6UpperBits) {
    char test = 0xFF;
    EXPECT_EQ(BitOperations::reset_n_upper_bits(test, 6), 3);
}

TEST(BitOperations, resetMoreThan8UpperBits) {
    char test = 0xFF;

    try {
        BitOperations::reset_n_upper_bits(test, 9);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "upper_bit_amount too large (>8)");
    }
}

/* 
set_n_upper_bits
 */ 

TEST(BitOperations, set4UpperBitsTo7) {
    char test = 0x00;
    EXPECT_EQ(BitOperations::set_n_upper_bits(test, 7, 4), 0x70);
}

TEST(BitOperations, set6UpperBitsTo5) {
    char test = 0x00;
    EXPECT_EQ(BitOperations::set_n_upper_bits(test, 5, 6), 0x14);
}

TEST(BitOperations, setUpperBitsToTooHighValue) {
    char test = 0x00;

    try {
        BitOperations::set_n_upper_bits(test, 4, 2);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "value_to_set too large for selected amount of bits");
    }
}

TEST(BitOperations, setMoreThan8UpperBits) {
    char test = 0x00;

    try {
        BitOperations::set_n_upper_bits(test, 4, 9);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "upper_bit_amount too large (>8)");
    }
}

/* 
read_n_upper_bits
 */ 

TEST(BitOperations, read3UpperBits) {
    char test = 0xFF;
    EXPECT_EQ(BitOperations::read_n_upper_bits(test, 2), 3);
}

TEST(BitOperations, read5UpperBits) {
    char test = 0x0F;
    EXPECT_EQ(BitOperations::read_n_upper_bits(test, 5), 1);
}

TEST(BitOperations, readMoreThan8UpperBits) {
    char test = 0x0F;
    try {
        BitOperations::read_n_upper_bits(test, 9);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "at most 8 bits can be read from a char");
    }
}

/* 
reset_n_lower_bits
 */ 

TEST(BitOperations, reset4LowerBits) {
    char test = 0xFF;
    EXPECT_EQ(BitOperations::reset_n_lower_bits(test, 4), 0xF0);
}

TEST(BitOperations, reset6LowerBits) {
    char test = 0xFF;
    EXPECT_EQ(BitOperations::reset_n_lower_bits(test, 6), 0xC0);
}

TEST(BitOperations, resetMoreThan8LowerBits) {
    char test = 0xFF;

    try {
        BitOperations::reset_n_lower_bits(test, 9);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "lower_bit_amount too large (>8)");
    }
}


/* 
set_n_lower_bits
 */ 

TEST(BitOperations, set4LowerBitsTo7) {
    char test = 0x00;
    EXPECT_EQ(BitOperations::set_n_lower_bits(test, 7, 4), 0x07);
}

TEST(BitOperations, set6LowerBitsTo5) {
    char test = 0x00;
    EXPECT_EQ(BitOperations::set_n_lower_bits(test, 5, 6), 0x05);
}

TEST(BitOperations, setLowerBitsToTooHighValue) {
    char test = 0x00;

    try {
        BitOperations::set_n_lower_bits(test, 4, 2);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "value_to_set too large for selected amount of bits");
    }
}

TEST(BitOperations, setMoreThan8LowerBits) {
    char test = 0x00;

    try {
        BitOperations::set_n_lower_bits(test, 4, 9);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "lower_bit_amount too large (>8)");
    }
}

/* 
read_n_lower_bits
 */ 

TEST(BitOperations, read3LowerBits) {
    char test = 0xFF;
    EXPECT_EQ(BitOperations::read_n_lower_bits(test, 2), 3);
}

TEST(BitOperations, read5LowerBits) {
    char test = 0x0F;
    EXPECT_EQ(BitOperations::read_n_lower_bits(test, 5), 15);
}

TEST(BitOperations, readMoreThan8LowerBits) {
    char test = 0x0F;
    try {
        BitOperations::read_n_lower_bits(test, 9);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "at most 8 bits can be read from a char");
    }
}

/* 
read_nth_lsb
 */ 

TEST(BitOperations, read3rdLsbit) {
    unsigned char test = 0xFF;
    EXPECT_EQ(BitOperations::read_nth_lsb(test, 3), 1);

    test = 0xF0;
    EXPECT_EQ(BitOperations::read_nth_lsb(test, 3), 0);
}

TEST(BitOperations, read7thLsbit) {
    unsigned char test = 0x80;
    EXPECT_EQ(BitOperations::read_nth_lsb(test, 7), 1);

    test = 0x70;
    EXPECT_EQ(BitOperations::read_nth_lsb(test, 7), 0);
}

TEST(BitOperations, readsMoreThan7thLsbit) {
    unsigned char test = 0x80;
    try {
        BitOperations::read_nth_lsb(test, 8);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "cannot read more than 7th lsbit in unsigned char");
    }
}

/* 
set_nth_lsb
 */ 

TEST(BitOperations, set3rdLsbit) {
    unsigned char test = 0xF0;
    EXPECT_EQ(BitOperations::set_nth_lsb(test, 3, true), 0xF8);

    test = 0xFF;
    EXPECT_EQ(BitOperations::set_nth_lsb(test, 3, false), 0xF7);
}

TEST(BitOperations, set7thLsbit) {
    unsigned char test = 0x0F;
    EXPECT_EQ(BitOperations::set_nth_lsb(test, 7, true), 0x8F);

    test = 0xFF;
    EXPECT_EQ(BitOperations::set_nth_lsb(test, 7, false), 0x7F);
}

TEST(BitOperations, setsMoreThan7thLsbit) {
    unsigned char test = 0x80;
    try {
        BitOperations::set_nth_lsb(test, 8, true);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "cannot set more than 7th lsbit in unsigned char");
    }
}

/* 
int16_to_char_arr
 */ 

TEST(BitOperations, convertInt16ToCharArr) {
    std::array<unsigned char,2> x = BitOperations::int16_to_char_arr(16705);
    EXPECT_THAT(x, testing::ElementsAreArray({0x41, 0x41}));
}

/* 
int32_to_char_arr
 */ 

TEST(BitOperations, convertInt32ToCharArr) {
    std::array<unsigned char,4> x = BitOperations::int32_to_char_arr(0x22aaccdd);
    EXPECT_THAT(x, testing::ElementsAreArray({0x22, 0xaa, 0xcc, 0xdd}));
}

/* 
char_arr_to_int16
 */ 

TEST(BitOperations, convertCharArrToInt16) {
    uint16_t x = BitOperations::char_arr_to_int16({0x41, 0x41});
    EXPECT_EQ(x, 16705);
}

/* 
char_arr_to_int32
 */ 

TEST(BitOperations, convertCharArrToInt32) {
    uint32_t x = BitOperations::char_arr_to_int32({0x00, 0x22, 0x12, 0x34});
    EXPECT_EQ(x, 0x00221234);
}

/*
int16_into_char_vector
*/
TEST(BitOperations, userSetsIndex2and3In5ElementVector) {
    std::vector<unsigned char> x = BitOperations::int16_into_char_vector(16705, {0x01, 0x02, 0x03, 0x04, 0x05}, 2);
    EXPECT_THAT(x, testing::ElementsAreArray({0x01, 0x02, 0x41, 0x41, 0x05}));
}

TEST(BitOperations, userSetsIndex2and3In3ElementVector) {
    try {
        BitOperations::int16_into_char_vector(16705, {0x01, 0x02, 0x03}, 2);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "start index too big or vector too small");
    }
}

/*
int32_into_char_vector
*/
TEST(BitOperations, userSetsIndex2to5In6ElementVector) {
    std::vector<unsigned char> x = BitOperations::int32_into_char_vector(0x22334455ul, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06}, 2);
    EXPECT_THAT(x, testing::ElementsAreArray({0x01, 0x02, 0x22, 0x33, 0x44, 0x55}));
}

TEST(BitOperations, userSetsIndex2to5In5ElementVector) {
    try {
        BitOperations::int32_into_char_vector(0x22334455ul, {0x01, 0x02, 0x03, 0x04, 0x05}, 2);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "start index too big or vector too small");
    }
}

/*
char_vector_to_int16
*/
TEST(BitOperations, userRetrievesIndex2And3In4ElementVector) {
    uint16_t x = BitOperations::char_vector_to_int16({0x01, 0x02, 0x03, 0x04}, 2);
    EXPECT_EQ(x, 0x0304);
}

TEST(BitOperations, userRetrievesIndex2And3In3ElementVector) {
    try {
        BitOperations::char_vector_to_int16({0x01, 0x02, 0x03}, 2);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "start index too big or vector too small");
    }
}

/*
char_vector_to_int32
*/
TEST(BitOperations, userRetrievesIndex2To5In6ElementVector) {
    uint32_t x = BitOperations::char_vector_to_int32({0x01, 0x02, 0x03, 0x04, 0x05, 0x06}, 2);
    EXPECT_EQ(x, 0x03040506ul);
}

TEST(BitOperations, userRetrievesIndex2To5In5ElementVector) {
    try {
        BitOperations::char_vector_to_int32({0x01, 0x02, 0x03, 0x04, 0x05}, 2);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "start index too big or vector too small");
    }
}