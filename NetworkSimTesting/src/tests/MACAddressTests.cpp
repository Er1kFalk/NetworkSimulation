#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../TestUtils/TestUtils.h"
#include <vector>

#include "MACAddress/MACAddress.h"
#include "MACAddress/MACAddressInterface.h"

TEST(MACAddressInterface, is_valid_mac_address) {
    MACAddressInterface *m = new MACAddress;
    std::vector<std::string> correct_macs = {
        "fa:2a:d2:A4:3a:4A", // mixed: lowercase+uppercase letters + numbers
        "AF:DE:DA:A1:D4:AA", // only uppercase letters + numbers
        "ae:1a:d4:ee:cd:f2", // only lowercase letters + numbers
        "aa:bb:cc:dd:ee:ff", // only lowercase letters
        "FF:DD:EE:CC:AA:BB", // only uppercase letters
        "12:34:56:78:90:43"  // only numbers
    };

    std::vector<std::string> correct_macs_testnames = {
        "LOWERCASE, UPPERCASE AND NUMBERS",
        "UPPERCASE AND NUMBERS",
        "LOWERCASE AND NUMBERS",
        "LOWERCASE ONLY",
        "UPPERCASE ONLY",
        "NUMBERS ONLY"
    };

    std::vector<std::string> wrong_macs = {
        "fa:2a:d2:A4:3a4A", // missing a colon at the end
        "fa:2a.d2:A4:3a.4A", //having seperators at the right place, but the seperator is not a colon
        "fg:2a:d2:A4:3a:4A", // having colons at the right places, but mac contains non-hex value (e.g. g)
        "fg:2a:d2:A4:3a:4A:cc" // mac address is too long (but contains correct hex values)
        "fg:2a:d2:A4:3a" // mac address is too short
    };

    std::vector<std::string> wrong_macs_testnames = {
        "MISSING COLON",
        "WRONG SEPERATORS",
        "NON HEX VALUES",
        "TOO LONG ADDRESS",
        "TOO SHORT ADDRESS"
    };

    for (std::string::size_type i = 0; i < correct_macs.size(); i++) {
        EXPECT_TRUE(m->is_valid_mac_address(correct_macs[i])) << TestUtils::generate_error_msg(correct_macs_testnames[i], "Mac should have been accepted but was rejected.");
    }

    for (std::string::size_type i = 0; i < wrong_macs.size(); i++) {
        EXPECT_FALSE(m->is_valid_mac_address(wrong_macs[i])) << TestUtils::generate_error_msg(wrong_macs[i], "Mac should have been rejected but was accepted.");
    }

    delete m;
}

TEST (MACAddressInterface, userTriesToSetAddressWithVectorOfLengthSix) {
    std::vector<unsigned char> correct_address = {0x01, 0x02, 0xbb, 0x44, 0xbf, 0x4a};

    MACAddressInterface *m = new MACAddress;

    // when we set the (correct) address, the getter should return that address back when we call it afterwards
    m->set_address(correct_address);
    EXPECT_THAT(m->get_address(), testing::ElementsAreArray(correct_address));
}

TEST (MACAddressInterface, userTriesToSetAddressWithVectorOfLengthThatIsNotSix) {
    std::vector<unsigned char> too_short_address = {0x01, 0x02, 0xbb, 0x44, 0xbf};
    std::vector<unsigned char> too_long_address = {0x01, 0x02, 0xbb, 0x44, 0xbf, 0x4a, 0x23};
    MACAddressInterface *m = new MACAddress;
    // setting too short / too long addresses should give us invalid arg except
    try {
         m->set_address(too_short_address);
         FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_THAT(m->get_address(), testing::Not(testing::ElementsAreArray(too_short_address)));
        EXPECT_STREQ(e.what(), "Address must have 6 octets (elements).");
    }

    try {
         m->set_address(too_long_address);
         FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_THAT(m->get_address(), testing::Not(testing::ElementsAreArray(too_long_address)));
        EXPECT_STREQ(e.what(), "Address must have 6 octets (elements).");
    }
}