#include "arduserialstream.h"
#include <string.h>

using namespace std;

int main(void){
	
	ArduSerialStream arduino("/dev/ttyUSB0");

	if (arduino.IsOpen()){
		cout << "connected" << endl;
	}else{
		cout << "Connection failure. Exiting..." << endl;
		return -1;
	}
	
	
	arduino << "Send this string" << endl;
	
	string received_string;
	arduino >> received_string;
	
}
