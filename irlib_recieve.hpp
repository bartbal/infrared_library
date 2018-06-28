// ==========================================================================
//
// File      : irlib_recieve.hpp
//
//
// ==========================================================================

// this file contains Doxygen lines
/// @file
#include <array>
namespace irlib{
    
    class irlib_recieve : public hwlib::pin_in {
        hwlib::target::pin_in reciever;
        int wait_us_time;
        
    public:
        
        /// \brief   
        /// recieve interface
        /// \details
        /// This class receives data that is being send with the irlib_transmit class
        irlib_recieve(hwlib::target::pin_in & reciever, int wait_us_time = 600):
            reciever( reciever ),
            wait_us_time( wait_us_time )
        {}
        
        /// \brief   
        /// get override
        /// \details
        /// Get had to be overriten. function didn't change from origional hwlib::pin_in.get(hwlib::buffering)
        bool get(hwlib::buffering) override{
            return reciever.get();
        }
        
        /// \brief   
        /// catch data after
        /// \details
        /// this function handels everything after the head. to catch the head use the irlib::listen_for_head() function
        unsigned int catch_data(){
            int temp = 1;
            unsigned int data = 0;
            unsigned int i = 31;
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
        /// wait for the correct head signal
        /// \details
        /// This function waits until it detects the correct head signal. when it detects the correct head is returns true.
        bool listen_for_head(){
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
                                                    if((hwlib::now_us() - now >= 2400) && (hwlib::now_us() - now < 2480)){
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
    };
    
}// end namespace irlib