#include "arduinointerface.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

//#define debug

ArduinoInterface::ArduinoInterface(ArduSerialStream * _arduino): arduino(_arduino)
{

}

void ArduinoInterface::delay(int ms){
    std::chrono::milliseconds dura(ms);
    std::this_thread::sleep_for(dura);
}

void ArduinoInterface::pinMode(int pin, Mode md){

    string mode = (md==INPUT)?"I":"O";
#ifdef debug
    cout << "P" << mode << std::setw(2) << std::setfill('0') << pin << ";" << endl ;
#endif
    (*arduino) << "P" << mode << std::setw(2) << std::setfill('0') << pin << ";";
}

void ArduinoInterface::digitalWrite(int pin, Status st){
#ifdef debug
    cout << "DW" << std::setw(2) << std::setfill('0') << pin << std::setw(1) << st << ";" << endl ;
#endif
    (*arduino) << "DW" << std::setw(2) << std::setfill('0') << pin << std::setw(1) << st << ";";
}

bool ArduinoInterface::digitalRead(int pin){
#ifdef debug
    std::cout << "DR" << std::setw(2) << std::setfill('0') << pin << ";" << endl;
#endif
    (*arduino) << "DR" << std::setw(2) << std::setfill('0') << pin << ";" ;
    bool returnValue;
    (*arduino) >> returnValue;
#ifdef debug
    cout << returnValue << endl;
#endif
    return returnValue;
}

int ArduinoInterface::analogRead(int pin){
    std::cout << "AR" << std::setw(2) << std::setfill('0') << pin << ";" << endl;
}
