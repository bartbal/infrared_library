// ==========================================================================
//
// File      : laser_game.hpp
// Copyright : bartvannetburg@hotmail.com 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// This file contains Doxygen lines
/// @file
#ifndef LASER_GAME
#define LASER_GAME

#include "hwlib.hpp"
#include "irlib.hpp"

namespace laser_game{
    
class game{
    hwlib::target::pin_out yellow_led = hwlib::target::pin_out( hwlib::target::pins::d4 );

    hwlib::target::pin_out live1 = hwlib::target::pin_out( hwlib::target::pins::d8 );
    hwlib::target::pin_out live2 = hwlib::target::pin_out( hwlib::target::pins::d9 );
    hwlib::target::pin_out live3 = hwlib::target::pin_out( hwlib::target::pins::d10 );

    hwlib::port_out_from_pins lives = hwlib::port_out_from_pins(live1, live2, live3);

    hwlib::target::pin_in trigger = hwlib::target::pin_in( hwlib::target::pins::d7 );
    hwlib::target::pin_in magazine = hwlib::target::pin_in( hwlib::target::pins::d6 );

    irlib::transmit transmitter = irlib::transmit();

    hwlib::target::pin_in reciever = hwlib::target::pin_in( hwlib::target::pins::d13 );
    irlib::recieve recieve = irlib::recieve(reciever);
    
    int live = 7;
    int ammo = 300;
    unsigned int data = 0;
    
    /// \brief   
    /// Check if player is being shot at
    /// \details
    /// This function checks if the ir sensor recieves the being shot data and if so it substracts lives and waits 5 seconds.
    void check_if_hit(){
        if(recieve.head()){
            data = recieve.get_uint_data();
            if(data == 10){
                yellow_led.set(1);
                
                live >>= 1;
                lives.set(live);
                
                for(unsigned int i = 0;i < 100;i++){
                    transmitter.pulse_one();
                }
                hwlib::wait_ms(100);
                for(unsigned int i = 0;i < 100;i++){
                    transmitter.pulse_one();
                }
                hwlib::wait_ms(100);
                for(unsigned int i = 0;i < 100;i++){
                    transmitter.pulse_one();
                }
                
                if(live == 0){
                    while(1){
                        if(recieve.get_uint() == 100){
                            live = 7;
                            lives.set(live);
                            break;
                        }
                    }
                }
                hwlib::wait_ms(4700);
                yellow_led.set(0);
            } else if (data == 100){
                live = 7;
                lives.set(live);
            }
        }
    }

    /// \brief   
    /// Reload the ammo
    /// \details
    /// This function realoads the ammo and waits about 5-6 seconds.
    void reload(){
        yellow_led.set(1);
       
        for(unsigned int i = 0;i < 150;i++){
            transmitter.pulse_one();
        }
        
        for(unsigned int i = 0;i < 50000;i++ ){ 
            check_if_hit();
        }
        
        for(unsigned int i = 0;i < 150;i++){
            transmitter.pulse_one();
        }
       
       for(unsigned int i = 0;i < 1000000;i++ ){ //5 seconds
            check_if_hit();
       }
       ammo = 300;
       yellow_led.set(0);
    }

    public:

    /// \brief   
    /// Construct the laser game class
    /// \details
    /// This class has all functions for a lasergame.
    game(){}

    /// \brief   
    /// Laser game function
    /// \details
    /// This function handles everything for the laser game tagger.
    void laser_game(){     
        lives.set(live);
        while(1){

            check_if_hit();
            
            if(!trigger.get()){
                if(ammo > 0){
                    transmitter.send_uint(10);
                    ammo--;
                }
            }
            if(!magazine.get()){
                reload();
            }
            hwlib::wait_us(1);
        }
    }

    /// \brief   
    /// Medic function
    /// \details
    /// This function is to create a box/gun that gives back all lives to a player.
    void medic(){
        yellow_led.set(1);
        live2.set(1);
        
        while(1){
            if(!trigger.get()){
                transmitter.send_uint(100);
            }
        }
    }

};


} //end namespace laser_game

#endif // LASER_GAME