// ==========================================================================
//
// File      : irlib_transmit.hpp
//
//
// ==========================================================================

// this file contains Doxygen lines
#include <algorithm>
#include <array>
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
        
        void sent_uint(unsigned int n){
            unsigned int m [32]; 
            std::fill(m, m+32, 0);
            unsigned int count = 0;
//            std::bitset <32> b = n;
//            b.flip();
            
            while(n != 0){
            m[count] = (n & 1);
//            hwlib::cout << (n & 1) << " n: " << n << "\n";

            n >>= 1;
            count++;
            }
            m[count] = 2;
            
            pulse_head();
            
            for(int i = 31; i > 0; i--){
                if(m[i] == 2){
                    i--;
                    for(int j = i; j >= 0; j--){
//                            hwlib::cout << m[j] << " test " << j << "\n";
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