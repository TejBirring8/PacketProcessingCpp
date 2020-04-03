//
// Created by tbirring on 05/10/2019.
//
#ifndef CODETEST_PACKET_PROCESSING_H
#define CODETEST_PACKET_PROCESSING_H
#include <cstdint>
#include <cassert>
#include <stdexcept>
#include <any>
#include <memory>
#include "packet_definitions/packet_definitions.h"


namespace packet_processing
{
    ReadPacketRef ReadPacket(std::istream input_stream);
}


#include "packet_processing.cpp"
#endif // CODETEST_PACKET_PROCESSING_H
