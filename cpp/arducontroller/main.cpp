#define debug

#include <iostream>
#include "arduserialstream.h"
#include "arduinointerface.h"

int main(int argc, char *argv[])
{

    //CONNECT TO ARDUINO
    ArduSerialStream arduinoSerial("/dev/ttyUSB0",SerialStreamBuf::BAUD_115200);
    arduinoSerial.openSerial();
    if(arduinoSerial.IsOpen()){
        cout << "Connection succeed" << endl;
    }else{
        cout << "Connection did NOT succeed" << endl;
        return -1;
    }

    ArduinoInterface arduino(&arduinoSerial);
    arduino.pinMode(3,OUTPUT);


    /********************************************************/

    //ARDUINO PROGRAM

    //blink
    while(true){
        if(arduino.digitalRead(8) == 1 ){
            arduino.digitalWrite(3,HIGH);
            arduino.delay(1000);
            arduino.digitalWrite(3,LOW);
            arduino.delay(1000);
        }else{
            arduino.delay(10);
        }
    }

    /********************************************************/

    //CLOSE ARDUINO CONNECTION
    arduinoSerial.closeSerial();

    return 0;
}
