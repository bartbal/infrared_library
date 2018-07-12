// ==========================================================================
//
// File      : irlib_transmit.hpp
// Copyright : bartvannetburg@hotmail.com 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file
#include <algorithm>
#include <array>
#include "hwlib.hpp"
namespace irlib{
    
    class transmit : public due::d2_36kHz {
        int wait_us_time;
        due::d2_36kHz transmitter = due::d2_36kHz();

    public:
        
        /// \brief   
        /// Transmit interface
        /// \details
        /// This class handels everything to transmit data over infrared
        transmit(int wait_us_time = 600):
            wait_us_time( wait_us_time )
        {}
        
        /// \brief   
        /// Send head signal
        /// \details
        /// Use this function to send the head signal. 
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
        /// Send end signal
        /// \details
        /// Use this function to send the end signal.
        void pulse_end(){
            transmitter.set(1);
            hwlib::wait_us(2400);
            transmitter.set(0);
            
            hwlib::wait_us(wait_us_time); //pause

        }
        
        /// \brief   
        /// Send a 0
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
        /// Send a 1
        /// \details
        /// Use this function to send a 1.
        void pulse_one(){
            transmitter.set(1);
            hwlib::wait_us(1200);
            transmitter.set(0);
            
            hwlib::wait_us(wait_us_time); //pause
        }
        
        /// \brief   
        /// Send an unsigned int
        /// \details
        /// Use this function to send an unsigned int. This also includes the head and end sign.
        void send_uint(unsigned int n){
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
        
        /// \brief   
        /// Send an unsigned int
        /// \details
        /// Use this function to send an unsigned int. This function does not send a head and end signal.
        void send_uint_withoud_end_head(unsigned int n){
            unsigned int m [32]; 
            std::fill(m, m+32, 0);
            unsigned int count = 0;
            
            while(n != 0){
                m[count] = (n & 1);

                n >>= 1;
                count++;
            }
            m[count] = 2;
                        
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
            
        }
        
        /// \brief   
        /// Send a char
        /// \details
        /// Use this function to send a char. This also includes the head and end sign.
        void send_char(char n){
            send_uint((unsigned int)n);
        }
        
        /// \brief   
        /// Send a char*
        /// \details
        /// Use this function to send a char*. This also includes the head and end sign.
        void send_string(char const * n){
            int count = 0;
            pulse_head();
            for(char const * i = n; *i; i++) {
                send_uint_withoud_end_head(n[count]);
                count++;
            }
            send_uint_withoud_end_head(0);
            pulse_end();
        }
        
        /// \brief   
        /// Send an uint*
        /// \details
        /// Use this function to send an uint*. This also includes the head and end sign.
        void send_uint_array(unsigned int *n){
            int count = 0;
            pulse_head();
            for(unsigned int * i = n; *i; i++) {
                send_uint_withoud_end_head(n[count]);
                count++;
            }
            send_uint_withoud_end_head(0);
            pulse_end();
        }
    };   
    
}// end irlib namespace