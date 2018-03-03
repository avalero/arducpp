/**
  @file: ArduSerialClient.h
  @brief: Definición de la Clase ArduSerialClient
*/


// fichero ArduSerialClient.cpp
// funciones y operadores de la clase ArduSerialClient

#include "arduserialstream.h"
#include <iostream>

using namespace std;
using namespace LibSerial;

void ArduSerialStream::openSerial()
{
    if (IsOpen()){
        closeSerial();
    }

    Open(serial);
    SetBaudRate( baudrate);
    SetCharSize( SerialStreamBuf::CHAR_SIZE_8);
    SetParity( SerialStreamBuf::PARITY_NONE);
    SetNumOfStopBits(1);
    SetFlowControl( SerialStreamBuf::FLOW_CONTROL_NONE);
    usleep(1000*1000);

}

void ArduSerialStream::closeSerial()
{
    if (IsOpen()){
        Close();
    }
}
