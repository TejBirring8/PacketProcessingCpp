//
// Created by tbirring on 08/10/2019.
//
#include <string>
#include "_packet_data_reader.h"
#include "_endianness.h"




void packet_processing::CheckStreamValidity(std::istream& input_stream, const std::string& function_name)
{
    if (input_stream.good())
        return;

    // if we're here, the stream is indicating an error!

    // 1. check if EOF char is handled poorly
    app::debug::Assert(
            "packet_processing::packet_definitions",
            "_PacketDataReader",
            function_name,
            input_stream.eof(),
            "Unhandled EOF from stream!");

    // 2. the stream is genuinely bad - R/W issues in runtime
    if (input_stream.bad())
        throw app::error_handling::bad_stream_error("R/W failed on stream!");
}




/* uint8_t */

template<packet_processing::Endianness Host, packet_processing::Endianness Target>
uint8_t packet_processing::_PacketDataReader<Host, Target>::_ReadUint8(std::istream& input_stream)
{
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    char buff[1];
    input_stream.read( buff, 1 );
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return (uint8_t)buff[0];
}




/* uint16_t */

template<>
uint16_t packet_processing::_PacketDataReader<packet_processing::Endianness::BIG, packet_processing::Endianness::BIG>::_ReadUint16(std::istream& input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint16_t buff{0};
    input_stream.read( (char*)&buff, 2);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return buff;
}

template<>
uint16_t packet_processing::_PacketDataReader<packet_processing::Endianness::LITTLE, packet_processing::Endianness::LITTLE>::_ReadUint16(std::istream& input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint16_t buff{0};
    input_stream.read( (char*)&buff, 2);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return buff;
}

template<>
uint16_t packet_processing::_PacketDataReader<packet_processing::Endianness::LITTLE, packet_processing::Endianness::BIG>::_ReadUint16(std::istream& input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint16_t buff{0};
    input_stream.read( (char*)&buff, 2);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return be16toh(buff);
}

template<>
uint16_t packet_processing::_PacketDataReader<packet_processing::Endianness::BIG, packet_processing::Endianness::LITTLE>::_ReadUint16(std::istream& input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint16_t buff{0};
    input_stream.read( (char*)&buff, 2);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return le16toh(buff);
}




/* uint32_t */

template<>
uint32_t packet_processing::_PacketDataReader<packet_processing::Endianness::BIG, packet_processing::Endianness::BIG>::_ReadUint32(std::istream &input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint32_t buff{0};
    input_stream.read( (char*)&buff, 4);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return buff;
}

template<>
uint32_t packet_processing::_PacketDataReader<packet_processing::Endianness::LITTLE, packet_processing::Endianness::LITTLE>::_ReadUint32(std::istream &input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint32_t buff{0};
    input_stream.read( (char*)&buff, 4);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return buff;
}

template<>
uint32_t packet_processing::_PacketDataReader<packet_processing::Endianness::LITTLE, packet_processing::Endianness::BIG>::_ReadUint32(std::istream &input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint32_t buff{0};
    input_stream.read( (char*)&buff, 4);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return be32toh(buff);
}

template<>
uint32_t packet_processing::_PacketDataReader<packet_processing::Endianness::BIG, packet_processing::Endianness::LITTLE>::_ReadUint32(std::istream &input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint32_t buff{0};
    input_stream.read( (char*)&buff, 4);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return le32toh(buff);
}




/* uint64_t */

template<>
uint64_t packet_processing::_PacketDataReader<packet_processing::Endianness::BIG, packet_processing::Endianness::BIG>::_ReadUint64(std::istream &input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint64_t buff{0};
    input_stream.read( (char*)&buff, 8);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return buff;
}

template<>
uint64_t packet_processing::_PacketDataReader<packet_processing::Endianness::LITTLE, packet_processing::Endianness::LITTLE>::_ReadUint64(std::istream &input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint64_t buff{0};
    input_stream.read( (char*)&buff, 8);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return buff;
}

template<>
uint64_t packet_processing::_PacketDataReader<packet_processing::Endianness::LITTLE, packet_processing::Endianness::BIG>::_ReadUint64(std::istream &input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint64_t buff{0};
    input_stream.read( (char*)&buff, 8);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return be64toh(buff);
}

template<>
uint64_t packet_processing::_PacketDataReader<packet_processing::Endianness::BIG, packet_processing::Endianness::LITTLE>::_ReadUint64(std::istream &input_stream) {
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    uint64_t buff{0};
    input_stream.read( (char*)&buff, 8);
    CheckStreamValidity(input_stream, std::string(__FUNCTION__));
    return le64toh(buff);
}
