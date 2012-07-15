/**
 * This file contains the Joystick class
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <string>
#include <vector>
#include <linux/input.h>
#include <stdint.h>

using namespace std;
/**
 * This class represents a joystick or gamepad connected to a USB port.
 */
class Joystick {
 private:
        /// User-supplied device name
        string devName;

        /// The file descriptor of the opened device
        int fd;

        /// Version of the joystick driver
        string driverVersion;

        /// Number of axes
        unsigned int axesNumber;

        /// Number of buttons
        unsigned int buttonsNumber;

        /// Joystick identifier string
        string identifierString;

        /// Axis mapping (TODO: understand what's this)
        uint8_t axisMapping[ABS_MAX + 1];

        /// Button mapping (TODO: understand what's this)
        uint16_t buttonMapping[KEY_MAX - BTN_MISC + 1];

        /// Button values
        char *buttons;

        /// Axis values
        double *axes;

        /**
         * Initialize the device. This must be done by the constructor.
         */
        void initDevice() throw (string);
        bool dataReady() throw (string);

        int* offset;
        int* max_value;
        int* min_value;

        bool calibrated;

 public:

        bool readCalibrationFile(string);

        bool is_calibrated(){return calibrated;}

        int getOffSet(int i){return offset[i];}
        int getMax(int i){return max_value[i];}
        int getMin(int i){return min_value[i];}

        /// Sets the offset, minimum, and maximum value
        void calibrate(string);

        /// This is used by the default constructor
        static const char *defaultDevice;

        /// Default constructor: every class should have one
        Joystick() throw (string);

        /// Other constructor, that allows to specify the device file
        Joystick(const string &device) throw (string);

        /**
         * Read events from the device and update its status.  You
         * MUST call it, if you want to have the latest data.
         */
        void refresh() throw (string);

        /**
         * @name Information about the joystick
         */
        //@{
        /**
         * Return number of axes
         */
        unsigned int getAxesNumber() {return axesNumber;}

        /**
         * Return number of buttons
         */
        unsigned int getButtonsNumber() {return buttonsNumber;}

        /**
         * Return driver version
         */
        string getDriverVersion() {return driverVersion;}

        /**
         * Return identifier string
         */
        string getIdentifierString() {return identifierString;}
        //@}

        /**
         * Return state of the specified axis
         */
        double getAxis(unsigned int axis) throw (string);
        
        /**
         * Returns state of the specified axis with a value between -1 and +1
         */
        double getNormalizedAxis(unsigned int axis) throw (string);

        /**
         * Return state of the specified button
         */
        bool getButton(unsigned int button) throw (string);

        /**
         * Return state of all axes
         */
        void getAxes(vector<double> &axesData);

        /**
         * Return state of all buttons
         */
        void getButtons(vector<bool> &buttonsData);

        /// Destructor
        virtual ~Joystick() throw (string);
};
#endif
