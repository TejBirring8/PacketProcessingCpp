#include <iostream>
#include <stdexcept>
#include <fstream>
#include "app/app.h"
#include "packet_processing/packet_processing.h"
#include "state_machine/state_machine.h"
using namespace app;
using namespace std;




static std::string filepath{};
static filebuf ptrFilebuf{};
static volatile bool terminate_processing{false};




void OpenFile() {
    debug::Print("opening file...");

    // 2. attempt to open binary stream
    ptrFilebuf.open(filepath, std::ifstream::in | std::ifstream::binary);
    if (!ptrFilebuf.is_open()) {
        app::error_handling::ExitOnError("Could not open specified file: " + filepath);
    }

    debug::Print("file opened.");
}




void CloseFile() {
    if (!ptrFilebuf.is_open()) return;

    debug::Print("closing file...");

    ptrFilebuf.close();
    if (ptrFilebuf.is_open()) {
        throw runtime_error("Could not close specified file: " + filepath);
    }

    debug::Print("file closed.");
}




void PrintHelp() {
    ui::Print("Usage: ./CodeTest <filename>");
}




void ParseArgs(int argsCount, char **argsArray)
{
    debug::Print("parsing arguments...");

    if (argsCount != 2) {
        PrintHelp();
        app::error_handling::ExitOnError("Invalid number of arguments passed.");
    }

    // TODO regex check format of arg 1

    // set arg 1
    filepath = argsArray[1];

    debug::Print("arguments parsed.");
}




void ProcessAPacket(uint8_t packet_type, std::any& packet)
{
    using namespace packet_definitions;
    debug::Assert("",
            "",
            __FUNCTION__,
            (packet_type == 0xFF && (!packet.has_value())) || (packet_type != 0xFF && packet.has_value()),
            "Pre-condition not met!");


    /*****      process packets      *****/
    if (packet.has_value())
    {

        /* retrieve packet data in its intended struct and handle */
        switch (packet_type) {


            // Battery Status Packet:
            case BatteryStatPacket::get_type(): {
                auto pkt = any_cast<BatteryStatPacket>(packet);
                // could move all output printing to state machine(?)
                ui::Print("B;" + to_string(pkt.timestamp_sec()) + ";" + pkt.rcvd_battery_status_str());
            }
            break;


            // Power Stats Packet:
            case PowerStatsPacket::get_type(): {
                unsigned long long power_mW = any_cast<PowerStatsPacket>(packet).rcvd_power_mW();
                unsigned long timestamp_s = any_cast<PowerStatsPacket>(packet).timestamp_sec();
                state_machine::UpdateStateMachine(timestamp_s, power_mW);
            }
            break;


            default:
                debug::Assert("",
                        "",
                        __FUNCTION__,
                        true,
                        "Unknown packet type not caught by exception!");
            break;
        } // switch (packet_type)

    }
    else //  if (!packet.has_value())
    {
        debug::Assert("","", __FUNCTION__, packet_type == 0xFF, "Unknown exit condition!");
        terminate_processing = true;
    }
}




void TryReadAPacket()
{
    // read packet from stream
    try
    {
        auto result = packet_processing::ReadPacket(istream(&ptrFilebuf));
        uint8_t packet_type = result.first;
        std::any& packet = result.second;
        ProcessAPacket(packet_type, packet);
    }
    catch (error_handling::bad_packet_type& e )
    {
        // if bad packet type, do nothing, the byte will be consumed by ReadPacket(...).
        // better luck next time with the next byte on stream as the packet_type.
        return;
    }
    catch (error_handling::bad_value_in_packet& e )
    {
        // ignore this packet, do not update the state machine with it.
        return;
    }
    catch (error_handling::erroneous_packet_received& e )
    {
        // ignore this packet, do not update the state machine with it.
        return;
    }
    catch (exception& e) // i.e. bad stream error, nothing we can do, exit.
    {
        app::error_handling::ExitOnError(e);
    }
    catch (...) // i.e. any other unexpected occurrences, don't know what to do, exit.
    {
        app::error_handling::ExitOnError("Failed to read packet from stream.");
    }
}




int main(int args_count, char* args_array[])
{
    ParseArgs(args_count, args_array);
    OpenFile();


        while (!terminate_processing) {
            TryReadAPacket();
        }


    CloseFile();
    return EXIT_SUCCESS;
}