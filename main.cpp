// ==========================================================================
//
// blink a led on PIOB pin 27 == arduino-due on-board LED
//
// This file is in the public domain.
//
// ==========================================================================

#include "hwlib.hpp"
#include "irlib.hpp"
//#include "catch.hpp"

void recieve_now(irlib::irlib_recieve & recieve, hwlib::pin_out & green_led, int ms = 200){
    int ledstate = 0;
    unsigned int length = 0;
    while(1){
        if(recieve.listen_for_head()){
            hwlib::wait_us(600);
            length = recieve.catch_data();
            hwlib::cout << "recieving data! : " << length << "\n";
            ledstate = !ledstate;
            green_led.set(ledstate);
        }
        hwlib::wait_ms(ms);
    }
}

void transmit(irlib::irlib_transmit & transmitter, hwlib::target::pin_in & button){
    while(1){
       if(!button.get()){
           transmitter.sent_uint(565293);
       }
       hwlib::wait_us(10);
   }
}

int main( void ){	
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // the on-board LED is connected to port B bit 27
   auto green_led = hwlib::target::pin_out( hwlib::target::pins::d4 );
   auto yellow_led = hwlib::target::pin_out( hwlib::target::pins::d3 );
   
//   auto transmitter = hwlib::target::pin_out( hwlib::target::pins::d10 );
   
   auto button = hwlib::target::pin_in( hwlib::target::pins::d7 );
   
   irlib::irlib_transmit transmitter = irlib::irlib_transmit();
   
   auto reciever = hwlib::target::pin_in( hwlib::target::pins::d11 );
   irlib::irlib_recieve recieve = irlib::irlib_recieve(reciever);
   
   

    recieve_now(recieve, green_led);
//    transmit(transmitter, button);
}

////////////////////////////////////test transmitter////////////////////////////////////////////////////
//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
//
//    irlib::irlib_transmit transmitter = irlib::irlib_transmit();
//    TEST_CASE( "construct transmitter" ){
//        irlib::irlib_transmit transmitter = irlib::irlib_transmit();
//        REQUIRE( &transmitter != nullptr  );  
//    }
//
//    TEST_CASE( "transmitter,  pulse head" ){
//            uint_fast64_t now = hwlib::now_us();
//            transmitter.pulse_head();
//            uint_fast64_t end = hwlib::now_us();
//            REQUIRE( (end - now) >= 2900 && (end - now) <= 3100 );
//    }
//
//    TEST_CASE( "transmitter,  pulse head" ){
//            uint_fast64_t now = hwlib::now_us();
//            transmitter.pulse_head();
//            uint_fast64_t end = hwlib::now_us();
//            REQUIRE( (end - now) >= 2900 && (end - now) <= 3100 );
//    }
//
//    TEST_CASE( "transmitter,  pulse end" ){
//            uint_fast64_t now = hwlib::now_us();
//            transmitter.pulse_end();
//            uint_fast64_t end = hwlib::now_us();
//            REQUIRE( (end - now) >= 2900 && (end - now) <= 3100 );
//    }
//
//    TEST_CASE( "transmitter,  pulse null" ){
//            uint_fast64_t now = hwlib::now_us();
//            transmitter.pulse_null();
//            uint_fast64_t end = hwlib::now_us();
//            REQUIRE( (end - now) >= 1700 && (end - now) <= 1900 );
//    }
//
//    TEST_CASE( "transmitter,  pulse one" ){
//            uint_fast64_t now = hwlib::now_us();
//            transmitter.pulse_one();
//            uint_fast64_t end = hwlib::now_us();
//            REQUIRE( (end - now) >= 1700 && (end - now) <= 1900 );
//    }
//
//    TEST_CASE( "transmitter, sent uint  " ){
//            uint_fast64_t now = hwlib::now_us();
//            transmitter.sent_uint(58663);
//            uint_fast64_t end = hwlib::now_us();
//            REQUIRE( (end - now) >= 34700 && (end - now) <= 34900 );
//    }
//////////////////////////////////////////////////////////////////////////////////
//auto reciever = hwlib::target::pin_in( hwlib::target::pins::d11 );
//   irlib::irlib_recieve recieve = irlib::irlib_recieve(reciever);
//    TEST_CASE( "construct reciever" ){
//        irlib::irlib_recieve recieve = irlib::irlib_recieve(reciever);
//        REQUIRE( &recieve != nullptr  );  
//    }
//
//    TEST_CASE( "recieve, recieve data  " ){
//        unsigned int data = 0;
//        while(1){
//            if(recieve.listen_for_head()){
//                hwlib::wait_us(600);
//                data = recieve.catch_data();
//            }
//            hwlib::wait_ms(ms);
//        }
//        REQUIRE( data ==  58663);
//    }
///////////////////////////////////////////////////////////////////////////////////
