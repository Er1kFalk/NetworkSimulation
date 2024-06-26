#include "ProtocolUtils.h"

/*
    COURTESY OF RFC1071 P.6
    https://datatracker.ietf.org/doc/html/rfc1071

    This have been modified a bit, since we are working with 8-bit values,
    that have to be converted to 16 bits
    */
unsigned short int ProtocolUtils::calculate_internet_checksum(std::vector<unsigned char> data) {
    unsigned int count = data.size();
    unsigned long int sum = 0;
    unsigned int addr = 0;
    while( count > 1 )  {
        unsigned short val16bit = (((unsigned short) data[addr])<<8) + data[++addr];
        /*  This is the inner loop */
        sum += val16bit;
        addr++;
        count -= 2;
    }

    /*  Add left-over byte, if any */
    if( count > 0 )
        sum += data[addr];

    /*  Fold 32-bit sum to 16 bits */
    while (sum>>16)
        sum = (sum & 0xffff) + (sum >> 16);

    return ~sum;
}

bool ProtocolUtils::verify_internet_checksum(std::vector<unsigned char> data, unsigned short int checksum) {
    unsigned int count = data.size();
    unsigned long int sum = 0;
    unsigned int addr = 0;
    while( count > 1 )  {
        unsigned short val16bit = (((unsigned short) data[addr])<<8) + data[++addr];
        /*  This is the inner loop */
        sum += val16bit;
        addr++;
        count -= 2;
    }

    /*  Add left-over byte, if any */
    if( count > 0 )
        sum += data[addr];

    sum+=checksum;

    /*  Fold 32-bit sum to 16 bits */
    while (sum>>16)
        sum = (sum & 0xffff) + (sum >> 16);

    return sum == 0xffff; // true if verified, false if not
}
