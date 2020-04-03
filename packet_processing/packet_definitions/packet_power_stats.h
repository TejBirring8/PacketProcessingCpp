//
// Created by tbirring on 10/10/2019.
//

#ifndef CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_POWER_STATS_H
#define CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_POWER_STATS_H


namespace packet_processing::packet_definitions {
    class PowerStatsPacket : public Packet<0x00, packet_processing::Endianness::BIG, 12> {
    private:
        uint32_t rcvd_voltage_volts_{0};
        uint64_t rcvd_current_milliamps_{0};
    public:
        // const
        explicit PowerStatsPacket(std::istream
                                  &byteInputStream) :
                Packet(byteInputStream)
         {
            rcvd_voltage_volts_ = PacketDataReader<target_endianness>::ReadUint32(get_stream_of_payload_bytes());
            app::debug::Print("Parsed: 'voltage': " + app::string::ToHexString(rcvd_voltage_volts_));

            rcvd_current_milliamps_ = PacketDataReader<target_endianness>::ReadUint64(get_stream_of_payload_bytes());
            app::debug::Print("Parsed: 'current': " + app::string::ToHexString(rcvd_current_milliamps_));
        }


        unsigned long long rcvd_power_mW() // uint should be okay too, since 0<=val<=1200
        {
            return static_cast<unsigned long long>(rcvd_voltage_volts_ * rcvd_current_milliamps_);
        }
    };
}


#endif // CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_POWER_STATS_H
