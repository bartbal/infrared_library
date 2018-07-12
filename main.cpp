#include "hwlib.hpp"
#include "irlib.hpp"
#include "laser_game.hpp"
#include "test_recieve.cpp"
#include "test_transmitter.cpp"

void send_data(){
    hwlib::target::pin_in trigger = hwlib::target::pin_in( hwlib::target::pins::d7 );
    irlib::transmit transmitter = irlib::transmit();
    
    while(1){
        if(!trigger.get()){
            char const *string;
            string = "hallo_hoe_gaat_het";
            transmitter.send_string(string);
        }
    }
}

void recieve_data(){
    hwlib::target::pin_in reciever = hwlib::target::pin_in( hwlib::target::pins::d13 );
    irlib::recieve recieve = irlib::recieve(reciever);
    
    unsigned int length = 64;
    unsigned int data[length];
    while(1){
        recieve.get_array(data, length);
        for(unsigned int i = 0; i < length; i++){
            hwlib::cout << data[i];
        }
        hwlib::cout << "\n";
    }
}

void recieve_string(){
    hwlib::target::pin_in reciever = hwlib::target::pin_in( hwlib::target::pins::d13 );
    irlib::recieve recieve = irlib::recieve(reciever);
    
    unsigned int length = 64;
    char data[length];
    while(1){
        recieve.get_string(data, length);
        for(unsigned int i = 0; i < length; i++){
            hwlib::cout << data[i];
        }
        hwlib::cout << "\n";
    }
}

int main( void ){	
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto laser_game = laser_game::game();
    
///////////////////////////send data///////////////////////////

//    send_data();
//    recieve_data();
//    recieve_string();

////////////////////////////laser game/////////////////////////

    laser_game.laser_game();
//    laser_game.medic();

////////////////////////////test///////////////////////////////

//    test_transmitter(true);
//    test_reciever(true);   
    
///////////////////////////////////////////////////////////////
}

