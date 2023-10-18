#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <sstream>
#include <string>

#include "EthertypeTests.h"
#include "Ethertype/EthertypeInterface.h"
#include "Ethertype/Ethertype.h"
#include "../TestUtils/TestUtils.h"

TEST(EthertypeInterface, userTriesToSetEthertypeWithVectorOfLengthTwo) {
    EthertypeInterface *e = new Ethertype;

    std::vector<std::vector<unsigned char>> correct_ethertypes = {
        {0x01, 0x02},
        {0x11, 0xAB},
        {0x21, 0x0B},
        {0xFF, 0xD2}
    };

    for (std::vector<unsigned char> eth : correct_ethertypes) {
        e->set_ethertype(eth);
        EXPECT_THAT(e->get_ethertype(), testing::ElementsAreArray(eth)) << TestUtils::generate_error_msg("Correct Ethertype", "Ethertype should have been set, but wasn't");
    }

    delete e;
}

TEST(EthertypeInterface, userTriesToSetEthertypeWithVectorThatIsNotLengthTwo) {
    EthertypeInterface *e = new Ethertype;
    std::vector<std::vector<unsigned char>> wrong_ethertypes = {
        {0x01}, // too short
        {0x01, 0x02, 0x03}, // too long
        {0x04, 0x05, 0xAB, 0x04} 
    };

    for (std::vector<unsigned char> eth : wrong_ethertypes) {
        try {
            e->set_ethertype(eth);
            FAIL();
        } catch (std::invalid_argument exc) {
            std::ostringstream expected_err;
            expected_err << "Ethertype should be " << e->get_octet_length() << " octets, but was " << eth.size() << " octets";
            EXPECT_THAT(exc.what(), testing::StrEq(expected_err.str()));
            EXPECT_THAT(e->get_ethertype(), testing::Not(testing::ElementsAreArray(eth)));
        }
    }

    delete e;
}

TEST(EthertypeInterface, userTriesToSetEthertypeWithStringThatIsACommonEthertype) {
    EthertypeInterface *e = new Ethertype;
    
    std::vector<std::string> accepted_strings = {
        "ipv4",
        "ipv6",
        "arp",
        "iPv4",
        "IPv4",
        "ArP",
        "ARP",
        "ipv6"
    };

    std::vector<std::vector<unsigned char>> expected_ethertype_values = {
        {0x08, 0x00}, // ipv4
        {0x86, 0xDD}, // ipv6
        {0x08, 0x06}, // arp
        {0x08, 0x00}, // iPv4
        {0x08, 0x00}, // IPv4
        {0x08, 0x06}, // ArP
        {0x08, 0x06}, // ARP
        {0x86, 0xDD} // iPv6
    };

    ASSERT_EQ(accepted_strings.size(), expected_ethertype_values.size());

    for (int i = 0; i < accepted_strings.size(); i++) {
        e->set_ethertype(accepted_strings[i]);
        EXPECT_THAT(e->get_ethertype(), testing::ElementsAreArray(expected_ethertype_values[i]));
        e->set_ethertype((std::vector<unsigned char>){0x00, 0x00}); // reset ethertype for next test
    }
}

TEST(EthertypeInterface, UserTriesToSetEthertypeWithStringThatIsNotACommonEthertype) {
    EthertypeInterface *e = new Ethertype;

    std::vector<std::string> wrong_strings = {
        "ip v4",
        "IP.v4",
        "A r P",
        "asdmn"
    };

    for (std::string s : wrong_strings) {
        std::vector<unsigned char> get_ether = e->get_ethertype();
        try {
            e->set_ethertype(s);
            FAIL();
        } catch (std::invalid_argument exc) {
            std::ostringstream expected_err;
            expected_err << "Conversion from string '" << s << "' to ethertype value does not exist.";
            EXPECT_THAT(exc.what(), testing::StrEq(expected_err.str()));
            EXPECT_THAT(e->get_ethertype(), testing::ElementsAreArray(get_ether));
        }
    }
}