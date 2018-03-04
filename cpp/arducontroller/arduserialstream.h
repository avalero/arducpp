#ifndef __ARDUSERIALSTREAM_H__
#define __ARDUSERIALSTREAM_H__

#include <iostream>
#include <SerialStream.h>

using namespace std;
using namespace LibSerial;

class ArduSerialStream : public SerialStream
{

public:
    // constructores
    ArduSerialStream(string serial,
					SerialStreamBuf::BaudRateEnum baudrate=SerialStreamBuf::BAUD_9600):
					serial(serial),baudrate(baudrate)
	{

    }
    ~ArduSerialStream(){
        closeSerial();
    }
    
    /**
      * Closes de Serial Port
      */
    void closeSerial();

    /**
      * Opens serial port
      */
    void openSerial();
    
private:
    string serial;
    SerialStreamBuf::BaudRateEnum baudrate;

};

#endif
