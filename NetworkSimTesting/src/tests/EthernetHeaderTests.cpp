#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "EthernetHeaderTests.h"
#include "EthernetFrame/EthernetFrameInterface.h"
#include "EthernetFrame/EthernetFrame.h"
#include <memory>

TEST(EthernetFrameInterface, userSetsEthernetFrameInterfaceAndConvertsItToArray) {
    std::unique_ptr<EthernetFrameInterface> etherframe (new EthernetFrame);

    etherframe->set_destination_address({0x00, 0x01, 0x02, 0x03, 0x04, 0x05});
    etherframe->set_source_address({0x07, 0x11, 0x12, 0x13, 0x54, 0xAA});
    etherframe->set_ethertype({0x08, 0x00});

    EXPECT_THAT(etherframe->header_to_array(), testing::ElementsAreArray({
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 
        0x07, 0x11, 0x12, 0x13, 0x54, 0xAA,
        0x08, 0x00
    }));
}
