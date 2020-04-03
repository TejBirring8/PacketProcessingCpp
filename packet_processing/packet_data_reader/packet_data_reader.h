//
// Created by tbirring on 08/10/2019.
//
#ifndef CODETEST_PACKET_PROCESSING_PACKET_DATA_READER_H
#define CODETEST_PACKET_PROCESSING_PACKET_DATA_READER_H
#include <cstdint>
#include <istream>
#include "../types.h"
#include "../helpers.h"
#include "_packet_data_reader.h"


namespace packet_processing
{
    template <Endianness target_endianness>
    class PacketDataReader;
}




template <packet_processing::Endianness target_endianness>
class packet_processing::PacketDataReader : protected packet_processing::_PacketDataReader<packet_processing::GetHostEndianness(), target_endianness>
{
public:
    static inline uint8_t ReadUint8(std::istream& input_stream);
    static inline uint16_t ReadUint16(std::istream& input_stream);
    static inline uint32_t ReadUint32(std::istream& input_stream);
    static inline uint64_t ReadUint64(std::istream& input_stream);
};




#include "packet_data_reader.cpp.inc"
#endif // CODETEST_PACKET_PROCESSING_PACKET_DATA_READER_H
