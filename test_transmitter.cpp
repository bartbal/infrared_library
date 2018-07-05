// ==========================================================================
//
// blink a led on PIOB pin 27 == arduino-due on-board LED
//
// This file is in the public domain.
//
// ==========================================================================

#include "hwlib.hpp"
#include "irlib.hpp"
#include "catch.hpp"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

TEST_CASE( "construct transmitter" ){
        irlib::irlib_transmit transmitter = irlib::irlib_transmit();
        REQUIRE( &transmitter != nullptr  );  
}

TEST_CASE( "transmitter,  pulse head" ){
        uint_fast64_t now = hwlib::now_us();
        transmitter.pulse_head();
        uint_fast64_t end = hwlib::now_us();
        REQUIRE( (end - now) >= 2900 && (end - now) <= 3100 );
}

TEST_CASE( "transmitter,  pulse head" ){
        uint_fast64_t now = hwlib::now_us();
        transmitter.pulse_head();
        uint_fast64_t end = hwlib::now_us();
        REQUIRE( (end - now) >= 2900 && (end - now) <= 3100 );
}

TEST_CASE( "transmitter,  pulse end" ){
        uint_fast64_t now = hwlib::now_us();
        transmitter.pulse_end();
        uint_fast64_t end = hwlib::now_us();
        REQUIRE( (end - now) >= 2900 && (end - now) <= 3100 );
}

TEST_CASE( "transmitter,  pulse null" ){
        uint_fast64_t now = hwlib::now_us();
        transmitter.pulse_null();
        uint_fast64_t end = hwlib::now_us();
        REQUIRE( (end - now) >= 1700 && (end - now) <= 1900 );
}

TEST_CASE( "transmitter,  pulse one" ){
        uint_fast64_t now = hwlib::now_us();
        transmitter.pulse_one();
        uint_fast64_t end = hwlib::now_us();
        REQUIRE( (end - now) >= 1700 && (end - now) <= 1900 );
}

TEST_CASE( "transmitter, sent uint  " ){
        uint_fast64_t now = hwlib::now_us();
        transmitter.sent_uint(58663);
        uint_fast64_t end = hwlib::now_us();
        REQUIRE( (end - now) >= 34700 && (end - now) <= 34900 );
}
