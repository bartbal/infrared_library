#ifndef RECIEVE_TEST
#define RECIEVE_TEST

#include "hwlib.hpp"
#include "irlib.hpp"


void reciever_test1_uint(){
    auto reciever = hwlib::target::pin_in( hwlib::target::pins::d13 );
    auto recieve = irlib::recieve(reciever);
    unsigned int data = 0;
    
    hwlib::cout << "Send a uint 10 to\n";
    data = recieve.get_uint();
    
    if(data == 10){
        hwlib::cout << "reciever_test1_uint SUCCES\n";
    } else {
        hwlib::cout << "reciever_test1_uint FAIL. Data: " << data << "\n";
    }
}

void reciever_test2_char(){
    auto reciever = hwlib::target::pin_in( hwlib::target::pins::d13 );
    auto recieve = irlib::recieve(reciever);
    unsigned int data = 0;
    
    hwlib::cout << "Send a char \"h\"\n";
    data = recieve.get_char();
    
    if(data == 'h'){
        hwlib::cout << "reciever_test2_char SUCCES\n";
    } else {
        hwlib::cout << "reciever_test2_char FAIL. Data: " << data << "\n";
    }
}

void reciever_test3_get_array(){
    auto reciever = hwlib::target::pin_in( hwlib::target::pins::d13 );
    auto recieve = irlib::recieve(reciever);
    bool succes = true;
    unsigned int data[5];
    
    hwlib::cout << "Send an unsigned int* 104, 97, 108, 108, 111\n";
    recieve.get_array(data, 5);
    
    if(data[0] != 104){
        succes = false;
    } else if(data[1] != 97){
        succes = false;
    } else if(data[2] != 108){
        succes = false;
    } else if(data[3] != 108){
        succes = false;
    } else if(data[4] != 111){
        succes = false;
    }
    
    if(succes){
        hwlib::cout << "reciever_test3_get_array SUCCES\n";
    } else {
        hwlib::cout << "reciever_test3_get_array FAIL. Data: " << data << "\n";
    }
}

void reciever_test4_get_string(){
    auto reciever = hwlib::target::pin_in( hwlib::target::pins::d13 );
    auto recieve = irlib::recieve(reciever);
    char const *test_string;
    test_string = "test_succes";
    char data[11];
    bool succes = true;
    
    hwlib::cout << "Send a char* \'test_succes\'\n";
    recieve.get_string(data, 11);
    
    for(unsigned int i = 0; i < 11; i++){
        if(test_string[i] != data[i]){
            succes = false;
            break;
        }
    }
    
    if(succes){
        hwlib::cout << "reciever_test4_get_string SUCCES\n";
    } else {
        hwlib::cout << "reciever_test4_get_string FAIL. Data: " << data << "\n";
    }
}

void test_reciever(bool pause = false){
    char n;
    if(pause){
        hwlib::cout << "pres eny key to continue with test 1\n";
        hwlib::cin >> n;
    }
    reciever_test1_uint();
    hwlib::cout << "\n";
    if(pause){
        hwlib::cout << "pres eny key to continue with test 2\n";
        hwlib::cin >> n;
    }
    reciever_test2_char();
    hwlib::cout << "\n";
    if(pause){
        hwlib::cout << "pres eny key to continue with test 3\n";
        hwlib::cin >> n;
    }
    reciever_test3_get_array();
    hwlib::cout << "\n";
    if(pause){
        hwlib::cout << "pres eny key to continue with test 4\n";
        hwlib::cin >> n;
    }
    reciever_test4_get_string();
    hwlib::cout << "\n";
    hwlib::cout << "\nDone testing reciever\n";
}

#endif // RECIEVE_TEST
