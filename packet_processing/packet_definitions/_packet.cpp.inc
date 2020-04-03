//
// Created by tbirring on 10/10/2019.
//
#include <istream>
#include "_packet.h"
#include "../packet_data_reader/packet_data_reader.h"


template < uint8_t PacketType, packet_processing::Endianness SourceEndianness, size_t PayloadSize >
packet_processing::packet_definitions::Packet< PacketType, SourceEndianness, PayloadSize>::
Packet(std::istream &byteInputStream)
{

// debug - ensure we're only here if packet type byte is of this packet type
    app::debug::Assert(
            "packet_processing::packet_definitions",
            "Packet",
            __FUNCTION__,
            byteInputStream.peek() == get_type(),
            "Wrong packet type!");

// consume "header" bytes - packet type
    rcvd_packet_type_ = PacketDataReader<target_endianness>::ReadUint8(byteInputStream);
    app::debug::Print("Received: 'packet type': " + app::string::ToHexString(rcvd_packet_type_));
    bytewise_sum_of_packet += rcvd_packet_type_;

// consume "header" bytes - timestamp in milliseconds
    rcvd_timestamp_ms_ = PacketDataReader<target_endianness>::ReadUint32(byteInputStream);
    app::debug::Print("Received: 'timestamp ms': " + app::string::ToHexString(rcvd_timestamp_ms_));
    bytewise_sum_of_packet += (rcvd_timestamp_ms_ & 0x000000FF);
    bytewise_sum_of_packet += (rcvd_timestamp_ms_ >> 8);
    bytewise_sum_of_packet += (rcvd_timestamp_ms_ >> 16);
    bytewise_sum_of_packet += (rcvd_timestamp_ms_ >> 24);

// consume payload bytes (to be used by subclass)
    for (int i = 0; i < size_payload; ++i)
    {
        uint8_t payloadByteAti = PacketDataReader<target_endianness>::ReadUint8(byteInputStream) ;
        bytewise_sum_of_packet += payloadByteAti;
        stream_rcvd_payload_.put(payloadByteAti);
    }
    app::debug::Print("Received: PAYLOAD: " + stream_rcvd_payload_.str());

// debug - print bytewise sum % 256
    app::debug::Print("Packet Sum: " + app::string::ToHexString(bytewise_sum_of_packet ));

// consume error check byte
    rcvd_err_check_ = PacketDataReader<target_endianness>::ReadUint8(byteInputStream);
    app::debug::Print("Received: 'error check': " + app::string::ToHexString(rcvd_err_check_));

// throw exception if this packet is erroneous i.e. bytewise sum % 256 != rcvd_err_check_ byte.
    if (is_erroneous())
    {
        throw app::error_handling::erroneous_packet_received();
    }
}