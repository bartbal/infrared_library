#ifndef TRANSMIT_TEST
#define TRANSMIT_TEST

#include "hwlib.hpp"
#include "irlib.hpp"

   
void transmitter_test1_head(){
    irlib::transmit transmitter = irlib::transmit();
    uint_fast64_t now = hwlib::now_us();
    transmitter.pulse_head();
    uint_fast64_t end = hwlib::now_us();
    
    if( (end - now) >= 2900 && (end - now) <= 3100 ){
        hwlib::cout << "Transmitter_test1_head SUCCES\n";
    } else {
        hwlib::cout << "Transmitter_test1_head FAIL. Time: "<< (end - now) <<  "\n";
    }
}

void transmitter_test2_end(){
    irlib::transmit transmitter = irlib::transmit();
    uint_fast64_t now = hwlib::now_us();
    transmitter.pulse_end();
    uint_fast64_t end = hwlib::now_us();
    
    if( (end - now) >= 2900 && (end - now) <= 3100 ){
        hwlib::cout << "Transmitter_test2_end SUCCES\n";
    } else {
        hwlib::cout << "Transmitter_test2_end FAIL. Time: "<< (end - now) <<  "\n";
    }
}

void transmitter_test3_null(){
    irlib::transmit transmitter = irlib::transmit();
    uint_fast64_t now = hwlib::now_us();
    transmitter.pulse_null();
    uint_fast64_t end = hwlib::now_us();
    
    if( (end - now) >= 1700 && (end - now) <= 1900 ){
        hwlib::cout << "Transmitter_test3_null SUCCES\n";
    } else {
        hwlib::cout << "Transmitter_test3_null FAIL. Time: "<< (end - now) <<  "\n";
    }
}

void transmitter_test4_one(){
    irlib::transmit transmitter = irlib::transmit();
    uint_fast64_t now = hwlib::now_us();
    transmitter.pulse_one();
    uint_fast64_t end = hwlib::now_us();
    
    if( (end - now) >= 1700 && (end - now) <= 1900 ){
        hwlib::cout << "Transmitter_test4_one SUCCES\n";
    } else {
        hwlib::cout << "Transmitter_test4_one FAIL. Time: "<< (end - now) <<  "\n";
    }
}

void transmitter_test5_send_uint(){
    irlib::transmit transmitter = irlib::transmit();
    uint_fast64_t now = hwlib::now_us();
    transmitter.send_uint(10);
    uint_fast64_t end = hwlib::now_us();
    transmitter.send_uint(10);
    
    if( (end - now) >= 13000 && (end - now) <= 14000 ){
        hwlib::cout << "Transmitter_test5_send_uint SUCCES\n";
    } else {
        hwlib::cout << "Transmitter_test5_send_uint FAIL. Time: "<< (end - now) <<  "\n";
    }
}

void transmitter_test6_send_uint_withoud_end_head(){
    irlib::transmit transmitter = irlib::transmit();
    uint_fast64_t now = hwlib::now_us();
    transmitter.send_uint_withoud_end_head(10);
    uint_fast64_t end = hwlib::now_us();
    
    if( (end - now) >= 7200 && (end - now) <= 7300 ){
        hwlib::cout << "transmitter_test6_send_uint_withoud_end_head succes\n";
    } else {
        hwlib::cout << "transmitter_test6_send_uint_withoud_end_head FAIL. Time: "<< (end - now) <<  "\n";
    }
}

void transmitter_test7_send_char(){
    irlib::transmit transmitter = irlib::transmit();
    uint_fast64_t now = hwlib::now_us();
    transmitter.send_char('h');
    uint_fast64_t end = hwlib::now_us();
    transmitter.send_char('h');
    
    if( (end - now) >= 18650 && (end - now) <= 18750 ){
        hwlib::cout << "transmitter_test7_send_char SUCCES\n";
    } else {
        hwlib::cout << "transmitter_test7_send_char FAIL. Time: "<< (end - now) <<  "\n";
    }
}

void transmitter_test8_send_uint_array(){
    irlib::transmit transmitter = irlib::transmit();
    unsigned int data[5];
    data[0] = 104;
    data[1] = 97;
    data[2] = 108;
    data[3] = 108;
    data[4] = 111;
    uint_fast64_t now = hwlib::now_us();
    transmitter.send_uint_array(data);
    uint_fast64_t end = hwlib::now_us();
    transmitter.send_uint_array(data);
    
    if( (end - now) >= 324900 && (end - now) <= 377650 ){
        hwlib::cout << "transmitter_test8_send_uint_array SUCCES\n";
    } else {
        hwlib::cout << "transmitter_test8_send_uint_array FAIL. Time: "<< (end - now) <<  "\n";
    }
}

void transmitter_test9_send_string(){
    irlib::transmit transmitter = irlib::transmit();
    char const *string;
    string = "test_succes";
    uint_fast64_t now = hwlib::now_us();
    transmitter.send_string(string);
    uint_fast64_t end = hwlib::now_us();
    transmitter.send_string(string);
    
    if( (end - now) >= 145500 && (end - now) <= 159000 ){
        hwlib::cout << "transmitter_test9_send_string SUCCES\n";
    } else {
        hwlib::cout << "transmitter_test9_send_string FAIL. Time: "<< (end - now) <<  "\n";
    }
}

void test_transmitter(bool pause = false){
    char n;
    transmitter_test1_head();
    transmitter_test2_end();
    transmitter_test3_null();
    transmitter_test4_one();
    hwlib::cout << "\n";
    if(pause){
        hwlib::cout << "pres eny key to continue with test 5. send 10\n";
        hwlib::cin >> n;
    }
    transmitter_test5_send_uint();
    hwlib::cout << "\n";
    transmitter_test6_send_uint_withoud_end_head();
    hwlib::cout << "\n";
    if(pause){
        hwlib::cout << "pres eny key to continue with test 7. send 'h' \n";
        hwlib::cin >> n;
    }
    transmitter_test7_send_char();
    hwlib::cout << "\n";
    if(pause){
        hwlib::cout << "pres eny key to continue with test 8. send 104, 97, 108, 108, 111 \n";
        hwlib::cin >> n;
    }
    transmitter_test8_send_uint_array();
    hwlib::cout << "\n";
    if(pause){
        hwlib::cout << "pres eny key to continue with test 9. send 'test_succes'\n";
        hwlib::cin >> n;
    }
    transmitter_test9_send_string();
    hwlib::cout << "\n";
    
    hwlib::cout << "\nDone testing transmitter\n";
}
    
#endif // TRANSMIT_TEST