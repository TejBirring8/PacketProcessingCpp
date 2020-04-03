# 'CodeTest' application (coding test)
Tej Birring (tejbirring8@gmail.com)
## Description
The CodeTest application reads binary-format (raw) packets from a file\*, generating a run-time object which corresponds to the particular packet type. The packet object is used to obtain useful information which is passed onto the system's state machine. 

\* The implementation allows for the binary file input stream to be replaced by any specialisation of `istream`, making the implementation conducive to a raw socket-based application, etc.

Another feature of the implementation is the ability to interpret *both* little-endian and big-endian ordered packets from the same input stream. It is trivial to add another packet type to the system ([*explained here*](#adding-a-new-packet-type)). The implementation automatically deals with endianness conversion of a packet's data to that of the host machine. *For performance reasons, the endianness of the host is set during compile-time and therefore NOT deduced dynamically at run-time.*

## Structure
The application source code is arranged under the following namespaces, the directory structure also corresponds to this arrangement.

* __app:__ All types and functions accessible to all/any part of the application source code are declared under this namespace. See `app/app.h`.
	* __error_handling:__ All exceptions (`std::exception` specialisations) and error handling functions used in the application are declared under this namespace.
	* __debug:__ All functions that are only compiled in if `COMPILE_FOR_DEBUG = true;` \(in `compile_options.h`\) reside under this namespace, such as `Assert(...)` and `Print(...)`.
	* __string:__ Functions that reside in this namespace are responsible for producing and manipulating strings.
	* __ui:__ Functions that reside under this namespace are responsible for command line I/O via `stdin`, `stdout`, and `stderr`.
	<br><br>
* __packet_processing:__ This namespace encapsulates all types and functions whose responsibility it is read, process, and abstract data obtained from raw packets via the input stream.
	* __packet_definitions:__ This namespace contains the class template `Packet` which is inherited to describe the various packet types that the system will interpret. <br> 
	*It is recommended NOT to modify the `Packet` class template (`_packet.h`, `_packet.cpp.inc`) and `_types.h` upon which it depends.*
	* __packet_data_reader:__ This namespace contains the PacketDataReader class responsible for encapsulating vital functions used to read raw data from the input stream to fixed integral types, and endianness conversion to host endianness if necessary.<br> 
	*It is recommended NOT to modify source code in this directory unless absolutely necessary, this is the lowest layer of the onion.* 
	<br><br>
* __state_machine:__ This namespace encapsulates all state machine logic associated with the power/battery monitoring system.<br> 
	*This could have been implemented as a Singleton or utilizing the State or Strategy pattern, however, encapsulating the source code in its own unique namespace was adequete given the low complexity.
    Utilizing the State pattern would have decreased readibilty as the relatively little code would've been distributed across numerous classes/files.*

```
                                     .─────────────────────.
                                    ([Source Code Root Dir] )
                                     `──────────┬──────────'
                                                │
              ┌─────────────────────────────────┼────────────────────────────────┬──────────────────────┐
              │                                 │                                │                      │
              │                                 │                                │                      │
              │                                 │                                │                      │
              ▼                                 ▼                                ▼                      ▼
┌─── ──── ──── ──── ──── ──┐    ┌─── ──── ──── ──── ──── ──── ─┐    ┌─── ──── ──── ──── ──── ┐    ┏━━━━━━━━━━┓
│           app            │    │      packet_processing       │    │     state_machine      │    ┃ main.cpp ┃
│                                                              │    │                        │    ┗━━━━━━━━━━┛
│  ┌─── ──── ──── ──── ─┐  │    │  ┌─── ──── ──── ──── ──── ┐                                │
   │   error_handling   │  │    │  │   packet_definitions   │  │    │    [state_machine/]
│   ──── ──── ──── ──── ┘  │    │  │                        │  │    │                        │
│                          │    │                           │  │    └─ ──── ──── ──── ──── ──┘
│  ┌─── ──── ──── ──── ─┐          │ [./packet_definitions]    │
│  │       debug        │  │    │  │                        │
    ──── ──── ──── ──── ┘  │    │  └─ ──── ──── ──── ──── ──┘  │
│                          │    │                              │
│  ┌─── ──── ──── ──── ─┐  │    │  ┌─── ──── ──── ──── ──── ┐  │
│  │       string       │          │   packet_data_reader   │  │
│   ──── ──── ──── ──── ┘  │    │  │                        │
                           │    │                           │  │
│  ┌─── ──── ──── ──── ─┐  │    │  │ [./packet_data_reader]    │
│  │         ui         │  │    │  │                        │  │
│   ──── ──── ──── ──── ┘          └─ ──── ──── ──── ──── ──┘  │
│                          │    │
                           │    │                              │
│          [app/]          │    │     [packet_processing/]     │
│                          │    │                              │
└─ ──── ──── ──── ──── ────      ──── ──── ──── ──── ──── ──── ┘

Fig 1. The namespace and directory structure of CodeTest source. 
       Text within squared brackets ("[]") indicate directory paths. 
```




## Development

### Style Guide
The source code should adhere to the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

### Adding a new packet type
The template class `Packet` is used to define all packet types that the system will read/process/utilize through static polymorphism, each packet type would therefore be represented by its own distinct class. 


```
                                             ┌────────────────────────────────────────┐
                                             │        <<metaclass parameters>>        │
                                             │                                        │
                                             │  ┌──────────────────────────────────┐  │
                                             │  │       uint8_t packet_type        │  │
                                             │  └──────────────────────────────────┘  │
                                             │  ┌──────────────────────────────────┐  │
                               ┌────────────◎│  │   Endianness source_endianness   │  │
                               │             │  └──────────────────────────────────┘  │
                               │             │  ┌──────────────────────────────────┐  │
                               ◎             │  │    size_t payload_size_bytes     │  │
              ┌──────────────────────────────┤  └──────────────────────────────────┘  │
              │                              │                                        │
              │          <<metaclass>>       └──┬─────────────────────────────────────┘
              │             Packet              │
              │                                 │
              └─────────────────────────────────┘
                               △
                               │
                               │
              ┌────────────────┴───────────────┬──────────────────────────────────────────────┐
              │                                │                                              │
              │                                │                                              │
              │                                │                                              │
┌───────────────────────────┐    ┌───────────────────────────┐                  ┌───────────────────────────┐
│                           │    │                           │     .      .     │                           │
│     BatteryStatPacket     │    │     PowerStatsPacket      │    ( )    ( )    │      <PacketType_N>       │
│                           │    │                           │     '      '     │                           │
└───────────────────────────┘    └───────────────────────────┘                  └───────────────────────────┘

Fig 2. A class diagram depicting the use of template class 'Packet' in defining packet types utilized by the system as unique classes.
```


The packet data is bound to the format illustrated by Fig 3. The size of payload, data endianness, and unique byte value used to distinguish the packet type, is determined by the template parameters passed during inheritance.

```
┌─────────────┐  ┌───────────────┐             ┌────────────────────────────────────────┐   ┌─────────────┐
│ packet_type │  │ timestamp_ms  │             │                payload                 │   │ error_check │
│  (1 byte)   │  │   (4 bytes)   │             │ (PacketType_N.payload_size # of bytes) │   │  (1 byte)   │
└─────────────┘  └───────────────┘             └────────────────────────────────────────┘   └─────────────┘
       │                 │                                          │                              │
       │                 │                                          │                              │
       │                 │                                          │                              │
       │                 │                                          │                              │
       │                 │                                          │                              │
       │                 │                                          │                              │
       │                 │                                          │                              │
       │     ╭───────────●───────────╮   ╭──────────────────────────●────────────────────────╮     │
       │     │                       │   │                                                   │     │
       │     │                       │   │                                                   │     │
   █■■■│■■■■■│■■■■■■■■■■■■■■■■■■■■■■■│■■■│■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■│■■■■■│■■■█
   █ ┌─▼──┐ ┌▼───┐ ┌────┐ ┌────┐ ┌───▼┐ ┏▼━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━━┓ ┏━━━▼┓ ┌──▼─┐ █
   █ │    │ │    │ │    │ │    │ │    │ ┃████┃ ┃████┃ ┃████┃ ┃████┃ ┃████┃ ┃████┃ ┃████┃ ┃████┃ │    │ █
   █ └────┘ └────┘ └────┘ └────┘ └────┘ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ ┗━━━━┛ └────┘ █
   █■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■█

                                               PacketType_N

Fig 3. Every packet of any packet type 'n' (n=[1...N], where N is the number of distinct packet types) must be prefixed
       with 'packet_type' and 'timestamp_ms', and appended by 'error_check'. Every packet type 'n' is associated with a 
       fixed-size payload. 

```



A class that represents a given packet type 'n' may create its own data abstraction around the data it retrieves from its payload, e.g.
PowerStatsPacket reads a `uint32_t rcvd_voltage_volts_` and `uint64_t rcvd_current_milliamps_` from its payload, but it only exposes 
`unsigned long long rcvd_power_mW()` as an means of retrieving data from the packet object. 

__See `packet_processing/packet_definitions/packet_power_stats.h` and `packet_processing/packet_definitions/packet_battery_stat.h` for examples of packet type implementation.__

__After implementation of a class associated with a packet type 'n' as a distinct `packet_*.h` file, where `*` is to be replaced by a unique and appropriate
name for the packet type, it must be included in `packet_definitions.h`, and handled in its `generate_packet(...)` function.__ e.g.

~~~
/* include packet definitions here: */
#include "packet_battery_stat.h"
#include "packet_power_stats.h"
#include "packet_randomized_data.h"

.
.
.

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
        case packet_definitions::RandomizedDataPacket::get_type():
            app::debug::Print("Detected: Randomized Data Packet");
            packet_alloc = packet_definitions::RandomizedDataPacket(input_stream);
            break;
        default:
            packet_alloc_.reset(); // when unknown packet type is passed, nothing is present in packet context.
            break;
    }

    return ReadPacketRef(packet_type, packet_alloc_);
}
~~~

`main.c`'s `ProcessAPacket(...)` function is responsible for casting and operating on packets successfully read from the stream.
 

## Building
CMake is the build system used to generate 'makefiles' for various platforms (OS and Processor Architectures). <br>
*Note: CMakeLists.txt is still extremely basic and requires work!*

#### Building on Linux/macOS
After setting variables in `compile_options.h`, in a terminal emulator execute the following commands:
~~~
$ cd <root dir>
$ mkdir build
$ cd build
$ cmake ..
$ make
~~~

#### Building for Windows
After setting variables in `compile_options.h`, run the 'Native Tools Command Prompt' bundled with Visual Studio, there should be an 'x86' and 'x86_64' variant, only the latter will be able to build for 'x64' target architecture. Execute the following commands:
~~~
$ cd <root dir>
$ mkdir build
$ cd build
$ cmake ..
$ dir
~~~

You should see a `CodeTest.sln` file generated in the build directory, this is a Visual Studio project file. You may open this file with Visual Studio, configure compiler/linker options (if required), and click 'Build' -> 'Build Solution' from the menu bar. 

### OS and Processor Architecture Support
Currently this application has been successfully built for the following platforms:

* Linux x86_64 (Ubuntu 18.04)<br>
  *(toolchain details unavailable at time of writing)*

* macOS x86_64 (Mojave [macOS 10.14])<br>
  *Apple LLVM version 10.0.1 (clang-1001.0.46.4)*

* Windows x86_64 (Windows 10)<br>
  *Microsoft (R) C/C++ Optimizing Compiler Version 19.15.26732.1*



