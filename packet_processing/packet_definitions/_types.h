//
// Created by tbirring on 09/10/2019.
//
#ifndef CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_TYPES_H
#define CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_TYPES_H
#include <cstdint>
#include <istream>
#include <sstream>
#include <iomanip>
#include "../../app/app.h"


namespace packet_processing::packet_definitions {
    template<size_t sizeOfPayload>
    class PayloadByteStreamBuffer;

    template<size_t sizeOfPayload>
    class PayloadByteStream;
}




template<size_t size_of_payload>
class packet_processing::packet_definitions::PayloadByteStreamBuffer : public std::basic_streambuf<char> {
private:
    uint8_t payload_[size_of_payload]{0};
public:
    PayloadByteStreamBuffer() {
        // sizeof(char) == sizeof(uint8_t) for this to work on a machine arch.
        // set the values of pointers: beginning (of array), current byte (in array), end (of array)
        setg((char *) &payload_[0], (char *) &payload_[0], ((char *) &payload_[0]) + size_of_payload);
        setp((char *) &payload_[0], ((char *) &payload_[0]) + size_of_payload);
    }

    // TODO improve efficiency of implementation
    std::string str() {
        std::stringstream sstream;
        sstream << "0x ";
        for (size_t i = 0; i < size_of_payload - 1; ++i) {
            sstream << app::string::ByteToHexString(payload_[i]) << " ";
        }
        sstream << app::string::ByteToHexString(payload_[size_of_payload - 1]);

        return sstream.str();
    }
};




template<size_t size_of_payload>
class packet_processing::packet_definitions::PayloadByteStream : public std::iostream {
private:
    PayloadByteStreamBuffer<size_of_payload> payload_buffer_;
public:
    PayloadByteStream() : payload_buffer_(), std::iostream(&payload_buffer_) {}

    PayloadByteStream(const PayloadByteStream &old) : std::iostream(&payload_buffer_) {
        payload_buffer_ = old.payload_buffer_;
    }

    std::string str() {
        return payload_buffer_.str();
    }
};


#endif // CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_TYPES_H
