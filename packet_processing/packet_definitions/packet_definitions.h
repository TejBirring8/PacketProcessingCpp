//
// Created by tbirring on 08/10/2019.
//
#ifndef CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_H
#define CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_H
#include <istream>
#include <map>
#include "../../app/app.h"






/* include packet definitions here: */
#include "packet_battery_stat.h"
#include "packet_power_stats.h"




typedef std::pair<uint8_t, std::any&> ReadPacketRef;
std::any packet_alloc_;




ReadPacketRef generate_packet(uint8_t packet_type, std::istream& input_stream )
{
    switch (packet_type)
    {
        case packet_definitions::BatteryStatPacket::get_type():
            app::debug::Print("Detected: Battery Stat Packet");
            packet_alloc_ = packet_definitions::BatteryStatPacket(input_stream);
            break;
        case packet_definitions::PowerStatsPacket::get_type():
            app::debug::Print("Detected: Power Stats Packet");
            packet_alloc_ = packet_definitions::PowerStatsPacket(input_stream);
            break;
        default:
            packet_alloc_.reset(); // when unknown packet type is passed, nothing is present in packet context.
            break;
    }

    return ReadPacketRef(packet_type, packet_alloc_);
}




#endif // CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_H
