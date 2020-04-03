#ifndef CODETEST_APP_H
#define CODETEST_APP_H
#include <string>
#include <stdexcept>


/* 'app' namespace declares generic functions used by all/any part of the application. */
namespace app
{
    namespace error_handling
    {
        // use this exception to indicate when input stream is bad.
        class bad_stream_error : std::runtime_error { public: explicit bad_stream_error(const std::string& message) : std::runtime_error(message) {} };

        // use this exception to indicate when error check has failed on packet.
        class erroneous_packet_received : std::runtime_error { public: explicit erroneous_packet_received() : std::runtime_error("Packet error check failed.") {} };

        // use this exception to convey when the value read from the packet is
        // out of range of what is expected for that particular packet type,
        // despite error check passing.
        class bad_value_in_packet : std::out_of_range { public: explicit bad_value_in_packet(const std::string& message) : std::out_of_range(message) {} };

        // use this exception to indicate if a bad packet type has been detected
        // on the stream.
        class bad_packet_type : std::out_of_range { public: explicit bad_packet_type() : std::out_of_range("Bad packet type.") {} };

        /* error-handling functions */
        void ExitOnError(const std::exception& e);
        void ExitOnError(const std::string& message, int _errno);
        void ExitOnError(const std::string& message);
    }




    /* 'app::debug' namespace declares generic functions only compiled in if 'COMPILE_FOR_DEBUG'
     * is set to 'true' in 'compile_options.h'. */
    namespace debug
    {
        void Print(const std::string& message);

        void Assert(
                const std::string& namespace_name,
                const std::string& class_name,
                const std::string& function_name,
                bool test_expression,
                const std::string& message);
    }




    /* 'app::string' namespace declares generic functions used to produce or manipulate strings. */
    namespace string
    {
        template< typename FixedSizeIntegralType >
        inline std::string ToHexString( FixedSizeIntegralType val );

        inline std::string ByteToHexString( uint8_t val );
    }




    /* 'app::string' namespace declares generic functions for UI. */
    namespace ui
    {
        void Print(const std::string &message);
    }
}


#include "app_string_functions.cpp.inc"
#endif // CODETEST_APP_H
