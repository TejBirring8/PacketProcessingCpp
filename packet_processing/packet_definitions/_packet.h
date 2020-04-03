//
// Created by tbirring on 10/10/2019.
//
#ifndef CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_PACKET_H
#define CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_PACKET_H
#include "_types.h"
#include "../types.h"


namespace packet_processing::packet_definitions
{
    // packet type - the byte specifying which packet (struct definition) is being read.
    template < uint8_t PacketType, Endianness SourceEndianness, size_t PayloadSize >
    class Packet;
}




/* this class represents a packet, implying basic formatting required for the system */
template < uint8_t packet_type, packet_processing::Endianness source_endianness, size_t size_of_payload_bytes >
class packet_processing::packet_definitions::Packet
{
public:
    static const constexpr Endianness target_endianness = source_endianness;
    static const constexpr size_t size_payload{size_of_payload_bytes};


private:
    uint8_t rcvd_packet_type_{0};
    uint32_t rcvd_timestamp_ms_{0};
    PayloadByteStream<size_payload> stream_rcvd_payload_;
    uint8_t rcvd_err_check_{0};
    uint8_t bytewise_sum_of_packet{0}; // for error checking


public:
    explicit Packet(std::istream& byteInputStream);

    // used for packet-type comparison
    static constexpr uint8_t get_type() { return packet_type; }

    // getters for "header" bytes and error check byte
    [[nodiscard]] uint8_t rcvd_packet_type() const { return rcvd_packet_type_; }
    [[nodiscard]] uint32_t rcvd_timestamp_ms() const { return rcvd_timestamp_ms_; }
    [[nodiscard]] uint8_t rcvd_err_check() const { return rcvd_err_check_; }
    [[nodiscard]] unsigned long timestamp_sec() { return static_cast<unsigned long>(rcvd_timestamp_ms_ / 1000); }

    // returns ref to istream encapsulating the payload buffer -
    // the istream ref is used by subclasses to access/parse payload data
    // using the PacketDataReader class.
    std::istream& get_stream_of_payload_bytes() { return stream_rcvd_payload_; }

    // check if this packet has errors : bytewise sum of all packet's bytes (excluding error check) % 256
    // (because uint8_t)
    bool is_erroneous() { return bytewise_sum_of_packet != rcvd_err_check_; }
};




#include "_packet.cpp.inc"
#endif // CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_PACKET_H