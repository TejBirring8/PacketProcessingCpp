//
// Created by tbirring on 05/10/2019.
//
#include <list>
#include <iostream>
#include "packet_processing.h"


ReadPacketRef packet_processing::ReadPacket(std::istream input_stream) {
    using namespace std;
    using namespace packet_processing;
    using namespace packet_processing::packet_definitions;

    CheckStreamValidity(input_stream, __FUNCTION__);

    // peek at first byte without consuming it - since
    // no preamble is used in packet formatting, this
    // must be a valid packet type!
    uint8_t buff_packet_type = input_stream.peek();
    app::debug::Print("Peek: " + app::string::ToHexString(buff_packet_type));

    // read the packet - initializing the struct that captures its context.
    ReadPacketRef res = generate_packet(buff_packet_type, input_stream);

    /* no packet read: */
    if (!res.second.has_value()) {
        // if we're here, it should only be EOF-state representational char (0xFF),
        // not because of any char read from the file.
        if (res.first == 0xFF) {
            app::debug::Print("EOF detected.");
            input_stream.get();
        }
        else {
            // unrecognized packet type!
            // in this case, we simply consume this byte (as garbage),
            // hoping that the next call to this function will see
            // a valid packet type.
            input_stream.get();
            throw app::error_handling::bad_packet_type();
        }
    }

    return res;
}
