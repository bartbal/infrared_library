// ==========================================================================
//
// blink a led on PIOB pin 27 == arduino-due on-board LED
//
// This file is in the public domain.
//
// ==========================================================================

#include "hwlib.hpp"
#include "irlib.hpp"
#include <array>


bool catch_head(hwlib::pin_in & reciever,  hwlib::pin_out & led){
    uint_fast64_t now = hwlib::now_us();
    while(1){
        if(!reciever.get()){
            now = hwlib::now_us();
            while(1){
                if(reciever.get()){
                    if((hwlib::now_us() - now >= 780) && (hwlib::now_us() - now < 880)){
                        while(1){
                            if(!reciever.get()){ 
                                if((hwlib::now_us() - now >= 1580) && (hwlib::now_us() - now < 1680)){
                                    while(1){
                                        if(reciever.get()){ 
                                            if((hwlib::now_us() - now >= 2380) && (hwlib::now_us() - now < 2480)){
                                                led.set(1);
                                                hwlib::wait_us(50);
                                                led.set(0);
                                                return true;
                                            } else {
                                                break;
                                            }
                                        }
                                    }
                                } else {
                                    break;
                                }
                            }
                        }
                    } else {
                        break;
                    }
                }
            }
        }
        hwlib::wait_us(1);
    }
}

void recieve_now(irlib::irlib_recieve & recieve, hwlib::pin_out & green_led, hwlib::pin_out & yellow_led, int ms = 200){
    int ledstate = 0;
    unsigned int length = 0;
    while(1){
        if(recieve.listen_for_head()){
            hwlib::wait_us(600);
            length = recieve.catch_data();
            hwlib::cout << "recieve HEAD! data = " << length << "\n";
            ledstate = !ledstate;
            green_led.set(ledstate);
        }
        hwlib::wait_ms(ms);
    }
}

void transmit(irlib::irlib_transmit & transmitter, hwlib::target::pin_in & button){
    while(1){
       if(!button.get()){
           transmitter.sent_uint(200);
//           transmitter.pulse_head();
//            ////////////////////////////////////
//               transmitter.pulse_one();
//               transmitter.pulse_null();    
//                
//                transmitter.pulse_one();
//               transmitter.pulse_null(); 
// 
//               transmitter.pulse_one();
//               transmitter.pulse_null(); 
// 
//               transmitter.pulse_one();
//               transmitter.pulse_null(); 
// 
//            ////////////////////////////////////              
//           transmitter.pulse_end();
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
   auto reciever = hwlib::target::pin_in( hwlib::target::pins::d11 );
   
   auto button = hwlib::target::pin_in( hwlib::target::pins::d7 );
   
   
   irlib::irlib_transmit transmitter = irlib::irlib_transmit();
   irlib::irlib_recieve recieve = irlib::irlib_recieve(reciever);
   

    recieve_now(recieve, green_led, yellow_led);
//    transmit(transmitter, button);

}
