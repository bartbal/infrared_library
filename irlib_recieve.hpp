// ==========================================================================
//
// File      : irlib_recieve.hpp
//
//
// ==========================================================================

// this file contains Doxygen lines
#include <array>
namespace irlib{
    
    class irlib_recieve : public hwlib::pin_in {
        hwlib::target::pin_in reciever;
        int wait_us_time;
        
        public:
        
        irlib_recieve(hwlib::target::pin_in & reciever, int wait_us_time = 600):
            reciever( reciever ),
            wait_us_time( wait_us_time )
        {}
        
    
        bool get(hwlib::buffering) override{
            return reciever.get();
        }
        
        int catch_length(hwlib::pin_out & yellow_led){
            int temp = 1;
            int data = 0;
            for(unsigned int i = 7; i > 0; i--){
                for(unsigned int j = 0; j < 2; j++){
                    hwlib::wait_us(100);
                    temp = temp & !reciever.get();
                    hwlib::wait_us(500);
                }
                data += (temp<<i);
                
                hwlib::wait_us(100);
                if(!reciever.get()){
                    yellow_led.set(1);
                    hwlib::wait_us(100);
                    yellow_led.set(0);
                    hwlib::cout << reciever.get() << " i'm broken i'm broken" << data << "\n";
                    break;
                }
                hwlib::wait_us(500);
                
                temp = 1;
            }
            return data;
        }
        
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