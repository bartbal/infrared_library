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

TEST_CASE( "construct reciever" ){
        irlib::irlib_recieve recieve = irlib::irlib_recieve(reciever);
        REQUIRE( &recieve != nullptr  );  
}

TEST_CASE( "recieve, recieve data  " ){
    unsigned int data = 0;
    while(1){
        if(recieve.listen_for_head()){
            hwlib::wait_us(600);
            data = recieve.catch_data();
        }
        hwlib::wait_ms(ms);
    }
    REQUIRE( data ==  58663);
}



