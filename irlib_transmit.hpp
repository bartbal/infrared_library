// ==========================================================================
//
// File      : irlib_transmit.hpp
//
//
// ==========================================================================

// this file contains Doxygen lines
#include "hwlib.hpp"
namespace irlib{
    
    class irlib_transmit : public due::d2_36kHz {
        int wait_us_time;
        due::d2_36kHz transmitter = due::d2_36kHz();

    public:
        
        irlib_transmit(int wait_us_time = 600):
            wait_us_time( wait_us_time )
        {}
        
        void pulse_head(){
            transmitter.set(1);
            hwlib::wait_us(800);
            transmitter.set(0);
            hwlib::wait_us(800);
            transmitter.set(1);
            hwlib::wait_us(800);
            transmitter.set(0);
            
            hwlib::wait_us(wait_us_time); //pause
        }
        
        void pulse_end(){
            transmitter.set(1);
            hwlib::wait_us(2400);
            transmitter.set(0);
            
            hwlib::wait_us(wait_us_time); //pause

        }
        
        void pulse_null(){
            hwlib::wait_us(600); //fisrt half of null
            transmitter.set(1);
            hwlib::wait_us(600);
            transmitter.set(0);
            
            hwlib::wait_us(wait_us_time); //pause
        }
        
        void pulse_one(){
            transmitter.set(1);
            hwlib::wait_us(1200);
            transmitter.set(0);
            
            hwlib::wait_us(wait_us_time); //pause
        }
    };   
    
}// end irlib namespace