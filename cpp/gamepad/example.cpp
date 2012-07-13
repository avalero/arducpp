#include "joystick.h"
#include <iostream>
#include <string.h>

using namespace std;

int main(void){

	//gamepad object
	Joystick* gamepad;
	
	//path to gamepad device
	string gamepadport = "/dev/input/js0";
	cout << "Connecting to gamepad at "<< gamepadport << endl;
	try{
		//try to connect with gamepad
		gamepad = new Joystick(gamepadport);
	}catch(string e){
		cout << "GamePad error. Exiting..." << endl;
		cout << e << endl;
		exit(1);
	}

	//load calibration file if exists. If not, calibrate the gamepad
	if (!gamepad->readCalibrationFile("joy_calibration.cfg")){
		gamepad->calibrate("joy_calibration.cfg");
	}

	//read all the values and events of the gamepad
    gamepad->refresh();

	//read the first four axes of your gamepad (normalized to [-1, +1] )
    for (unsigned int i=0; i<4; i++){
        cout << i << " ";
        cout << gamepad->getAxis(i);
        cout << endl;
	}
}
