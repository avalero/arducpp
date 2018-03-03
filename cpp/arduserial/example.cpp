#include "arduserialstream.h"
#include <string.h>

using namespace std;

int main(void){
	
	ArduSerialStream arduino("/dev/ttyUSB0",SerialStreamBuf::BAUD_9600);

	if (arduino.IsOpen()){
		cout << "connected" << endl;
	}else{
		cout << "Connection failure. Exiting..." << endl;
		return -1;
	}
	
	arduino << "Hola" << endl; //Send string "hola" thorugh serial port
	string line;
	arduino >> line; //receive string from serial port
	cout << line << endl;
	arduino.close();
}
