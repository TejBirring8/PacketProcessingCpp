//
// Created by tbirring on 09/10/2019.
//
#include "_packet.h"

#ifndef CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_BATTERY_STAT_H
#define CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_BATTERY_STAT_H




namespace packet_processing::packet_definitions {
    class BatteryStatPacket : public Packet<0x01, Endianness::BIG, 1> {
    private:
        uint8_t rcvd_battery_status_{0};
    public:
        explicit BatteryStatPacket(std::istream &byteInputStream) : Packet(byteInputStream) {

            rcvd_battery_status_ = PacketDataReader<target_endianness>::ReadUint8(get_stream_of_payload_bytes());

            app::debug::Print("Parsed: 'battery status': " + app::string::ToHexString(rcvd_battery_status_));
        }


        enum class BatteryStatus {
            VLOW = 0, LOW = 1, MED = 2, HIGH = 3
        };


        static std::string battery_status_to_string(BatteryStatus batteryStatus)
        {
            switch (batteryStatus) {
                case BatteryStatus::VLOW:
                    return "VLOW";
                case BatteryStatus::LOW:
                    return "LOW";
                case BatteryStatus::MED:
                    return "MED";
                case BatteryStatus::HIGH:
                    return "HIGH";
            }
        }


        [[nodiscard]] BatteryStatus rcvd_battery_status() const {
            if (rcvd_battery_status_ > 3)
                throw app::error_handling::bad_value_in_packet("Value indicating battery status is out of range, must be: 0<=val<=3 .");
            else return static_cast<BatteryStatus>(rcvd_battery_status_);
        }


        std::string rcvd_battery_status_str() const { return battery_status_to_string(rcvd_battery_status()); }
    };
}




#endif // CODETEST_PACKET_PROCESSING_PACKET_DEFINITIONS_BATTERY_STAT_H
