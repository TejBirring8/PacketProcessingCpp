//
// Created by tbirring on 08/10/2019.
//
#ifndef CODETEST_PACKET_PROCESSING_HELPERS_H
#define CODETEST_PACKET_PROCESSING_HELPERS_H
#include "types.h"
#include "../compile_options.h"


namespace packet_processing {
    inline constexpr packet_processing::Endianness GetHostEndianness()
    {
        return HOST_IS_BIG_ENDIAN ? packet_processing::Endianness::BIG : packet_processing::Endianness::LITTLE;
    }
}


#endif // CODETEST_PACKET_PROCESSING_HELPERS_H
