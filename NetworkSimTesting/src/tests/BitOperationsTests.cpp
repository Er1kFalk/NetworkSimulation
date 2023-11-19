#include "BitOperationsTests.h"
#include "../../../NetworkSimulation/src/BitOperations/BitOperations.h"
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
        EXPECT_STREQ(e.what(), "Value too large for selected amount of bits");
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