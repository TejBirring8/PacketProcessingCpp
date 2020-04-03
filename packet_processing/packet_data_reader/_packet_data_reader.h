//
// Created by tbirring on 08/10/2019.
//
#ifndef CODETEST_PACKET_PROCESSING__PACKET_DATA_READER_H
#define CODETEST_PACKET_PROCESSING__PACKET_DATA_READER_H
#include <cstdint>
#include <istream>
#include "../types.h"
#include "../helpers.h"


namespace packet_processing {
    template<Endianness host_endianness, Endianness target_endianness>
    class _PacketDataReader;

    inline void CheckStreamValidity(std::istream& input_stream, const std::string& function_name);
}


/* reads data from target device (specified endianness),
 * converting to this CPU (host's) endianness if required.
 */
template<packet_processing::Endianness host_endianness, packet_processing::Endianness target_endianness>
class packet_processing::_PacketDataReader {
protected:
    static inline uint8_t _ReadUint8(std::istream &input_stream);

    static inline uint16_t _ReadUint16(std::istream &input_stream);

    static inline uint32_t _ReadUint32(std::istream &input_stream);

    static inline uint64_t _ReadUint64(std::istream &input_stream);
};





#include "_packet_data_reader.cpp.inc"
#endif // CODETEST_PACKET_PROCESSING__PACKET_DATA_READER_H

