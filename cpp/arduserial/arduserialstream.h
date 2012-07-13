#ifndef __ARDUSERIALCLIENT_H__
#define __ARDUSERIALCLIENT_H__

#include <iostream>
#include <SerialStream.h>

using namespace std;
using namespace LibSerial;

class ArduSerialStream : public SerialStream
{

public:
    // constructores
    ArduSerialStream(){};
    ArduSerialStream(string serial):serial(serial){
        openSerial();
    }
    ~ArduSerialStream(){
        if (IsOpen()) closeSerial();
    }

private:
    // Member Functions

    /**
      * Opens serial port
      * @param serial The serial port
      */
    void openSerial();
    /**
      * Closes de Serial Port
      */
    void closeSerial();

private:
    string serial;

};

#endif
