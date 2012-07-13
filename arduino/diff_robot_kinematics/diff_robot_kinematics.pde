#include <Servo.h>

//arduino pins where the servos are connected to
int servoLeftPin = 9;
int servoRightPin = 13;

Servo servoleft;
Servo servoright;

//max linear speed in cm/sec
double max_speed = 14.333333;

//max angular speed in rad/sec
double max_jog = 3.53; 

//distance among wheels in cm
double d = 8.5;

double control_speed, control_jog;

//value at which servos do not move
int stop_right = 80;
int stop_left = 80;


//speeds in cm/sec at which robot moves when servo is set to 0,1,2,3,4 ... 10
double speeds[11] = {
  0 , 1.33333 , 3.6 , 5.8 , 8 , 9.66667 ,11.2 , 12.5333 , 13.6667 , 14, 14.3333};

void setup() {                

  servoleft.attach(servoLeftPin);
  servoright.attach(servoRightPin);

  //Set robot speed to 0
  controlRobot(0,0);

}

double getControlValue(double speed){
  //cannot go faster than max speed
  if (speed > max_speed) return 11;

  //check the control value for going at the desired speed
  double control_value=11;
  for (int i=0;i<11;i++){
    if (abs(speed) <= speeds[i]){
      control_value = i;
      break;
    }
  }

  //if speed was negative invert control value
  if (speed < 0) control_value = -control_value;
  return control_value;
}

//kinematic model of the robot. It passes real linear and angular speeds
//of the robot to individual speeds of each wheel.
void kinematics(double v, double w, double &lw, double &rw){
  rw = (2*v + d*w)/2;
  if (rw > max_speed) rw = max_speed; 

  lw = -d*w + rw;
}

//function that sets the speed of each servo to move the robot at
// v(cm/sec) and w (rad/sec)
void controlRobot(double v, double w){

  if (w>max_jog) w=max_jog;
  //in case the linear speed is too high let's assure at least we get the angular speed
  if ( v > ( (2*max_speed-d*abs(w))/2 ) )  
    v = (2*max_speed-d*abs(w))/2; 

  double vr,vl;  
  kinematics(v,w,vr,vl);

  double rw,lw;
  rw = getControlValue(vr);
  lw = getControlValue(vl);

  servoright.write(stop_right - rw);
  servoleft.write(stop_left + lw);  

}

void loop(){

  //move the robot at 5 cm/sec and 0.1 rad/sec
  controlRobot(5,0.1);

}

