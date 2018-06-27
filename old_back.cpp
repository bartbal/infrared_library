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

void pulse_head(due::d2_36kHz & transmitter){
    transmitter.set(1);
    hwlib::wait_us(800);
    transmitter.set(0);
    hwlib::wait_us(800);
    transmitter.set(1);
    hwlib::wait_us(800);
    transmitter.set(0);
    hwlib::wait_us(600); //pause
}

void pulse_end(due::d2_36kHz & transmitter){
    transmitter.set(1);
    hwlib::wait_us(2400);
    transmitter.set(0);
    
    hwlib::wait_us(600); //pause

}

void pulse_null(due::d2_36kHz & transmitter){
    hwlib::wait_us(600); //fisrt half of null
    transmitter.set(1);
    hwlib::wait_us(600);
    transmitter.set(0);
    
    hwlib::wait_us(600); //pause
}

void pulse_one(due::d2_36kHz & transmitter){
    transmitter.set(1);
    hwlib::wait_us(1200);
    transmitter.set(0);
    hwlib::wait_us(600); //pause
}

void transmit(due::d2_36kHz & transmitter, hwlib::pin_in & button, hwlib::pin_out & led, int ms = 20){
    while(1){
        if(!button.get()){
            led.set(1);
            pulse_head(transmitter);    //3300us 
            pulse_one(transmitter);     //5400us
            pulse_null(transmitter);    //7500us
            pulse_end(transmitter);     //9300us
            led.set(0);
            hwlib::wait_ms(200);
        }

    }
}

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

void recieve(hwlib::pin_in & reciever, hwlib::pin_out & yellow_led, hwlib::pin_out & green_led, int ms = 200){
    int ledstate = 0;
    while(1){
        if(catch_head(reciever, yellow_led)){
            hwlib::cout << "recieve HEAD!\n";
            ledstate = !ledstate;
            green_led.set(ledstate);
        }
        hwlib::wait_ms(ms);
    }
}

void fast_recieve(hwlib::pin_in & reciever, hwlib::pin_out & led, hwlib::pin_in & button, int us = 1){
    bool old_temp = 1;
    int temp = 1;
    int time = 0;
    while(1){
        if(!button.get()){
            temp = reciever.get();
            if(old_temp == 0 && temp == 1){
                hwlib::cout << "_______" << time << "_________________\n";
                time = 0;
            }
            old_temp = temp;
            time++;
        }
        hwlib::wait_us(us);
    }
}

int main( void ){	
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
    the on-board LED is connected to port B bit 27
   auto green_led = hwlib::target::pin_out( hwlib::target::pins::d4 );
   auto yellow_led = hwlib::target::pin_out( hwlib::target::pins::d3 );
   
   auto transmitter = hwlib::target::pin_out( hwlib::target::pins::d10 );
   auto reciever = hwlib::target::pin_in( hwlib::target::pins::d11 );
   
   auto button = hwlib::target::pin_in( hwlib::target::pins::d7 );
   
   

   
//   auto d2_36khz = due::d2_36kHz();
//        transmitter.set(1);
//    transmitter.set(0);
    recieve(reciever, yellow_led, green_led);
//    fast_recieve(reciever, yellow_led, button);
//    transmit(d2_36khz, button, green_led);

}
