// ==========================================================================
//
// File      : irlib_recieve.hpp
// Copyright : bartvannetburg@hotmail.com 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file
#include <array>
#include <algorithm>
namespace irlib{
    
    class recieve : public hwlib::pin_in {
        hwlib::target::pin_in reciever;
        int wait_us_time;
        
    public:
        
        /// \brief   
        /// Recieve interface
        /// \details
        /// This class receives data that is being send with the irlib_transmit class.
        recieve(hwlib::target::pin_in & reciever, int wait_us_time = 600):
            reciever( reciever ),
            wait_us_time( wait_us_time )
        {}
        
        /// \brief   
        /// Get() override
        /// \details
        /// Get() had to be overridden. Function didn't change from original hwlib::pin_in.get(hwlib::buffering).
        bool get(hwlib::buffering) override{
            return reciever.get();
        }
        
        /// \brief   
        /// Get unsigned int
        /// \details
        /// This function handels everything after the head for catching a simple unsigned int. To catch the head use the irlib::listen_for_head() function.
        unsigned int get_uint_data(){
            int temp = 1;
            unsigned int data = 0;
            unsigned int i = 31;
            hwlib::wait_us(600);
            for(; i > 0; i--){
                for(unsigned int j = 0; j < 2; j++){
                    hwlib::wait_us(100);
                    temp = temp & !reciever.get();
                    hwlib::wait_us(500);
                }
                
                hwlib::wait_us(100);
                if(!reciever.get()){
                    break;
                }
                hwlib::wait_us(500);
                
                data += (temp<<i);
                temp = 1;
            }
            data = data>>(i+1);
            
            return data;
        } 

        /// \brief   
        /// Wait for the head signal and get uint
        /// \details
        /// This function checks for a head signal and gets the data that comes after and returns it as an unsigned int.
        unsigned int get_uint(){
            unsigned int data = 0;
            while(1){
                if(head()){
                    data = get_uint_data();
                    return data;
                }
                hwlib::wait_us(1);
            }
        }
        
        /// \brief   
        /// Wait for the head signal and get char
        /// \details
        /// This function checks for a head signal and gets the data that comes after and returns it as a char.
        char get_char(){
            return (char)get_uint();
        }
        
        /// \brief   
        /// Check for head signal
        /// \details
        /// This function checks for a head signal. Best to be used in a loop. int wiggle_time defines the minimal time for the first pulse of the head signal this is set at 200 by default.
        /// This is to still recieve the head even if it mist the beginning of the head pulse. The maximum for this number should be 800. Everything above 800 nolonger follows the bart protocol.
        bool head(unsigned int wiggle_time = 200){
            uint_fast64_t now = hwlib::now_us();
                if(!reciever.get()){
                    now = hwlib::now_us();
                    while(1){
                        if(reciever.get()){
                            if((hwlib::now_us() - now >= wiggle_time) && (hwlib::now_us() - now < 900)){
                                while(1){
                                    if(!reciever.get()){ 
                                        if((hwlib::now_us() - now >= 1580) && (hwlib::now_us() - now < 1680)){
                                            while(1){
                                                if(reciever.get()){ 
                                                    if((hwlib::now_us() - now >= 2380) && (hwlib::now_us() - now < 2480)){
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
            return false;
        }
        
        
        
        /// \brief   
        /// Get array with bytes
        /// \details
        /// This function handels everything after the head for catching an array with bytes. To catch the head use the irlib::listen_for_head() function. 
        /// This function requires an array with the correct size to be passed as parameter. Also the length of this array has to be geven.
        /// Feel free to play with the timing. Decreasing or increasing it might give better results. Default timing is 387.
        unsigned int get_array_data(unsigned int *n, unsigned int lenght, int timing = 387){
            std::fill(n, n+lenght, 0);
            bool end = false;
            int temp = 1;
            unsigned int data = 0;
            unsigned int i = 7;
            hwlib::wait_us(600);
            for(unsigned int h = 0; h < lenght+1; h++){
                
                data = 0;
                for(; i > 0; i--){
                    for(unsigned int j = 0; j < 2; j++){
                        hwlib::wait_us(200);
                        temp = temp & !reciever.get();
                        hwlib::wait_us(400);
                    }
                    
                    hwlib::wait_us(200);
                    if(!reciever.get()){
                        end = true;
                        break;
                    }

                    hwlib::wait_us(timing); //default 387 us 

                    
                    data += (temp<<i);
                    temp = 1;

                }
                data = data>>(i+1);
                n[h] = data;
                i = 7;
                if(end){
                    break;
                }
            }            
            return data;
        } 
        
        /// \brief   
        /// Get array with bytes
        /// \details
        /// This function handels everything for catching an array with bytes.
        /// This function requires an array with the correct size to be passed as parameter. Also the length of this array has to be given.
        /// Feel free to play with the timing. Decreasing or increasing it might give better results. Default timing is 387.
        void get_array(unsigned int *n, unsigned int lenght, int timing = 387){
            while(1){
                if(head()){
                    get_array_data(n, lenght, timing);
                    break;
                }
            }
        }
        
        /// \brief   
        /// Get array with chars
        /// \details
        /// This function handels everything for catching an array with chars.
        /// This function requires an array with the correct size to be passed as parameter. Also the length of this array has to be given.
        /// Feel free to play with the timing. Decreasing or increasing it might give better results. Default timing is 385.
        void get_string(char *n, unsigned int lenght, int timing = 385){
            unsigned int data[lenght];
            while(1){
                if(head()){
                    get_array_data(data, lenght, timing);
                    for(unsigned int i = 0; i < lenght; i++){
                        n[i] = (char)data[i];
                    }
                    break;
                }
            }
        }
        
        
    };
    
}// end namespace irlib