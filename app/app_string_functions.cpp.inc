//
// Created by Tej Birring on 15/10/2019.
//
#include <string>
#include <sstream>
#include <iomanip>
#include "app.h"


template< typename FixedSizeIntegralType >
std::string app::string::ToHexString( FixedSizeIntegralType val )
{
    using namespace std;
    stringstream sstream;
    sstream << "0x " << setfill ('0') << setw(sizeof(FixedSizeIntegralType)*2) << hex;

    if (is_same<FixedSizeIntegralType, uint8_t>::value)
    {
        sstream << static_cast<unsigned short>(val);
    }

    if (is_same<FixedSizeIntegralType, uint16_t>::value)
    {
        sstream << static_cast<unsigned int>(val);
    }

    if (is_same<FixedSizeIntegralType, uint32_t>::value)
    {
        sstream << static_cast<unsigned long>(val);
    }

    if (is_same<FixedSizeIntegralType, uint64_t>::value)
    {
        sstream << static_cast<unsigned long long>(val);
    }


    std::string str = sstream.str();


    if (is_same<FixedSizeIntegralType, uint32_t>::value)
    {
        str.insert(5, " ");
        str.insert(8, " ");
        str.insert(11, " ");
    }

    if (is_same<FixedSizeIntegralType, uint64_t>::value)
    {
        str.insert(5, " ");
        str.insert(8, " ");
        str.insert(11, " ");
        str.insert(14, " ");
        str.insert(17, " ");
        str.insert(20, " ");
        str.insert(23, " ");
    }

    return str;
}


std::string app::string::ByteToHexString(uint8_t val)
{
    using namespace std;
    stringstream sstream; // TODO optimize!
    sstream << setfill ('0') << setw(2) << hex << static_cast<unsigned short>(val);
    return sstream.str();
}