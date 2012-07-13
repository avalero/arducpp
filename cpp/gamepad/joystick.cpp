/**
 @file: joytick.cpp
 @brief: Definición de la clase Joytick
*/

#include <errno.h>
#include <fcntl.h>
#include <linux/joystick.h>
#include <sstream>
#include <cstring>
#include <iostream>
#include <fstream>

#include "joystick.h"

using namespace std;

const char *Joystick::defaultDevice = "/dev/input/js0";

void Joystick::initDevice() throw (string)
{
    calibrated=false;
        int a;
        unsigned char c;
        char s[255];
        ostringstream oss;
        fd = open(devName.c_str(), O_RDONLY);
        if (fd < 0) {
                throw string("Unable to open device ") + devName + ": " +
                        strerror(errno);
        }
        ioctl(fd, JSIOCGVERSION, &a);
        oss << (a >> 16) << "." <<  ((a >> 8) & 0xff) << "." << (a & 0xff);
        driverVersion = oss.str();
        ioctl(fd, JSIOCGAXES, &c);
        axesNumber = c;
        axes = new double[axesNumber];
        offset = new int[axesNumber];
        max_value = new int[axesNumber];
        min_value = new int[axesNumber];
        ioctl(fd, JSIOCGBUTTONS, &c);

//modificación en vez de variable c pongo 20
        buttonsNumber = c;
        buttons = new char[buttonsNumber];
        ioctl(fd, JSIOCGNAME(255), &s);
        identifierString = s;
        ioctl(fd, JSIOCGAXMAP, buttonMapping);
        ioctl(fd, JSIOCGBTNMAP, buttonMapping);
}

void Joystick::calibrate(string filename){

    for (unsigned int i=0; i<getAxesNumber();i++){
        max_value[i]=0;
        min_value[i]=0;
        offset[i]=0;

    }

    cout << "Do not touch anything" << endl;
    usleep(1000*2000); //2 secs usleep(1000*1000);
    refresh();


    for (unsigned int i=0; i < getAxesNumber(); i++){
        offset[i]=getAxis(i);
    }

    cout << "Move the axes to their max and min positions" << endl;
    for (int j=0;j<50;j++){
        refresh();
        for (unsigned int i=0; i < getAxesNumber(); i++){
            max_value[i]=(getAxis(i)>max_value[i])?getAxis(i):max_value[i];
            min_value[i]=(getAxis(i)<min_value[i])?getAxis(i):min_value[i];
        }
        usleep(1000*100);
        cout << 10 - j/5 << " seconds remaining" << endl;
    }

    cout << "calibration values: " << endl;

    for (unsigned int i=0; i < getAxesNumber(); i++){
        cout << "axis " << i ;
        cout << ": offset " << offset[i];
        cout << ". min " << min_value[i];
        cout << ". max " << max_value[i];
        cout << endl;
    }

    ofstream calibration(filename.c_str());
    if (calibration.is_open()){
        calibration << getAxesNumber() << " ";
        for (unsigned int i=0; i < getAxesNumber(); i++){
            calibration << offset[i] << " ";
            calibration << min_value[i] << " ";
            calibration << max_value[i] << " ";
        }

        calibration << endl;
        calibration.close();
    }


}

bool Joystick::dataReady() throw (string)
{
        struct timeval timeout;
        int a;
        bool retval = true;
        fd_set readfds;
        // Arrigo hates select()
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        // Timeout 0 means "don't wait"
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000;
        a = select(fd + 1, &readfds, NULL, NULL, &timeout);
        if (a == 0) {
                retval = false;
        } else if (a < 0) {
                throw string("error in select(): ") + strerror(errno);
        }
        return retval;
}

void Joystick::refresh() throw (string)
{
        struct js_event event;
        ostringstream oss;
        //int dataRead = 0, dataToRead = getButtonsNumber() + getAxesNumber();
        // We can just read one event for each button or axis.
        // But some of them may be blocking.
        while (dataReady()) {
                if (read(fd, &event, sizeof(event)) != sizeof(event)) {
                        throw string("Unable to read events: ") + strerror(errno);
                }
                //dataRead++;
                // JS_EVENT_INIT could be superimposed to event information
                switch (event.type & ~JS_EVENT_INIT) {
                case JS_EVENT_BUTTON:
                        buttons[event.number] = event.value;
                        break;
                case JS_EVENT_AXIS:
                    axes[event.number] = 2.0*(event.value - offset[event.number])
                            /(max_value[event.number]-min_value[event.number]);
                        break;
                default: // Should happen only if driver changes
                        oss << "Unknown event type: " << event.type;
                        throw oss.str();
                }
        }
        //else printf("No data to be read\n");
}

double Joystick::getAxis(unsigned int axis) throw (string)
{
        if (axis >= axesNumber) {
                ostringstream oss;
                oss << "Wrong axis number specified: " << axis;
                throw oss.str();
        }
        return axes[axis];
}

bool Joystick::getButton(unsigned int button) throw (string)
{
        if (button >= buttonsNumber) {
                ostringstream oss;
                oss << "Wrong button number specified: " << button;
                throw oss.str();
        }
        return buttons[button];
}

void Joystick::getAxes(vector<double> &axesData)
{
        unsigned int i;
        axesData.resize(axesNumber);
        for (i = 0; i < axesNumber; i++) {
                axesData[i] = axes[i];
        }
}

void Joystick::getButtons(vector<bool> &buttonsData)
{
        unsigned int i;
        buttonsData.resize(buttonsNumber);
        for (i = 0; i < buttonsNumber; i++) {
                buttonsData[i] = buttons[i];
        }
}

bool Joystick::readCalibrationFile(string filename){
    ifstream calibration(filename.c_str());
    if (!calibration.is_open()){
        calibrated=false;
        return false;
    }

    unsigned int num;
    calibration >> num;
    if (num != getAxesNumber()){
        throw string("Calibration file incorrect. Please calibrate");
    }

    for (unsigned int i=0; i < num; i++){
        calibration >> offset[i];
        calibration >> min_value[i];
        calibration >> max_value[i];
    }

    calibrated = true;
    return true;
}

Joystick::Joystick() throw (string): devName(defaultDevice)
{
    try{
        initDevice();
    }catch(string e){
        throw e;
    }

    //readCalibrationFile();
}

Joystick::Joystick(const string &device) throw(string): devName(device)
{
    try{
        initDevice();
    }catch(string e){
        throw e;
    }

    //readCalibrationFile();
}

Joystick::~Joystick() throw(string)
{
        int a;
        a = close(fd);
        if (a < 0) {
                throw string("Unable to close device ") + devName + ": " +
                        strerror(errno);
        }
        delete [] buttons;
        delete [] axes;
}
