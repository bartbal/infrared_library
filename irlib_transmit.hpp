// ==========================================================================
//
// File      : irlib_transmit.hpp
//
//
// ==========================================================================

// this file contains Doxygen lines
/// @file
#include <algorithm>
#include <array>
#include "hwlib.hpp"
namespace irlib{
    
    class irlib_transmit : public due::d2_36kHz {
        int wait_us_time;
        due::d2_36kHz transmitter = due::d2_36kHz();

    public:
        
        /// \brief   
        /// transmit interface
        /// \details
        /// This class handels everything to transmit data over infrared
        irlib_transmit(int wait_us_time = 600):
            wait_us_time( wait_us_time )
        {}
        
        /// \brief   
        /// send head signal
        /// \details
        /// use this function to send the head signal. 
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
        
        /// \brief   
        /// send end signal
        /// \details
        /// Use this function to send the end signal.
        void pulse_end(){
            transmitter.set(1);
            hwlib::wait_us(2400);
            transmitter.set(0);
            
            hwlib::wait_us(wait_us_time); //pause

        }
        
        /// \brief   
        /// send a 0
        /// \details
        /// Use this function to send a 0.
        void pulse_null(){
            hwlib::wait_us(600); //fisrt half of null
            transmitter.set(1);
            hwlib::wait_us(600);
            transmitter.set(0);
            
            hwlib::wait_us(wait_us_time); //pause
        }
        
        /// \brief   
        /// send a 1
        /// \details
        /// Use this function to send a 1.
        void pulse_one(){
            transmitter.set(1);
            hwlib::wait_us(1200);
            transmitter.set(0);
            
            hwlib::wait_us(wait_us_time); //pause
        }
        
        /// \brief   
        /// send an unsigned int
        /// \details
        /// Use this function to send an unsigned int. this also includes the head and end sign.
        void sent_uint(unsigned int n){
            unsigned int m [32]; 
            std::fill(m, m+32, 0);
            unsigned int count = 0;
            
            while(n != 0){
            m[count] = (n & 1);

            n >>= 1;
            count++;
            }
            m[count] = 2;
            
            pulse_head();
            
            for(int i = 31; i > 0; i--){
                if(m[i] == 2){
                    i--;
                    for(int j = i; j >= 0; j--){
                        if(m[j]){
                            pulse_one();
                        } else {
                            pulse_null();
                        }                        
                    }
                    break;
                }
            }
            
            pulse_end();
        }
    };   
    
}// end irlib namespace