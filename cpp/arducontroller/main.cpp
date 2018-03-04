#include <iostream>
#include "arduserialstream.h"


using namespace std;

int digitalPin = 13;
bool state = false;

int main(int argc, char *argv[])
{
    ArduSerialStream arduino("/dev/ttyUSB0");
    arduino.openSerial();
    if(arduino.IsOpen()){
        cout << "Connection succeed" << endl;
    }else{
        cout << "Connection did NOT succeed" << endl;
        return -1;
    }

    cout << "Introduce número pin digital: " ;
    cin >> digitalPin;

    cout << "Introduce estado del pin " << digitalPin << " (0 - LOW, 1 - HIGH): " ;
    cin >> state;

    if(digitalPin < 10){
        arduino << "DW0" << digitalPin << state << ";" ;
#ifdef debug
        cout <<  "DW0" << digitalPin << state << ";" << endl;
#endif
    }else{
        arduino << "DW" << digitalPin << state << ";" ;//<< endl;
#ifdef debug
        cout << "DW" << digitalPin << state << ";" << endl;
#endif
    }

    arduino.closeSerial();

    return 0;
}
