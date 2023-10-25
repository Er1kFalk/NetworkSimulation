#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <sstream>
#include <string>

#include "EthertypeTests.h"
#include "Ethertype/EthertypeInterface.h"
#include "Ethertype/Ethertype.h"
#include "../TestUtils/TestUtils.h"

TEST(EthertypeInterface, userTriesToSetEthertypeWithStringThatIsACommonEthertype) {
    EthertypeInterface *e = new Ethertype({0, 0});
    
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
        e->set_ethertype((std::array<unsigned char, 2>){0x00, 0x00}); // reset ethertype for next test
    }
}

TEST(EthertypeInterface, UserTriesToSetEthertypeWithStringThatIsNotACommonEthertype) {
    EthertypeInterface *e = new Ethertype({0, 0});
    
    std::vector<std::string> wrong_strings = {
        "ip v4",
        "IP.v4",
        "A r P",
        "asdmn"
    };

    for (std::string s : wrong_strings) {
        std::array<unsigned char, 2> get_ether = e->get_ethertype();
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