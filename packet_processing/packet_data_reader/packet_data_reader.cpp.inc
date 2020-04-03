//
// Created by tbirring on 08/10/2019.
//
#include "packet_data_reader.h"
using namespace packet_processing;




template <Endianness target_endianness>
uint8_t PacketDataReader<target_endianness>::ReadUint8(std::istream& input_stream)
{
    // return
    return _PacketDataReader<GetHostEndianness(), target_endianness>::_ReadUint8(input_stream);
}




template <Endianness target_endianness>
uint16_t PacketDataReader<target_endianness>::ReadUint16(std::istream& input_stream)
{
    // return
    return _PacketDataReader<GetHostEndianness(), target_endianness>::_ReadUint16(input_stream);
}




template <Endianness target_endianness>
uint32_t PacketDataReader<target_endianness>::ReadUint32(std::istream& input_stream)
{
    // return
    return _PacketDataReader<GetHostEndianness(), target_endianness>::_ReadUint32(input_stream);
}




template <Endianness target_endianness>
uint64_t PacketDataReader<target_endianness>::ReadUint64(std::istream& input_stream)
{
    // return
    return _PacketDataReader<GetHostEndianness(), target_endianness>::_ReadUint64(input_stream);
}
