#ifndef ARDUINOINTERFACE_H
#define ARDUINOINTERFACE_H

#include "arduserialstream.h"


typedef enum{
    LOW,
    HIGH
} Status;

typedef enum{
    INPUT,
    OUTPUT
} Mode;

class ArduinoInterface
{
public:
    ArduinoInterface(ArduSerialStream* _arduino);

    void delay(int ms);
    void digitalWrite(int pin, Status st);
    bool digitalRead(int pin);
    int analogRead(int pin);
    void pinMode(int pin, Mode md);

private:
    ArduSerialStream* arduino;
};

#endif // ARDUINOINTERFACE_H
