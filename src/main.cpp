#include <iostream>
#include <string>

#include "Drone/Drone.h"
#include "Drone/Config.h"


//---------------------Variables Globales de Configuration--------------------//


//********Fichiers de Config*******//
char* config_file="config.ini";


//********Ports*******//
std::string Radio = "/dev/xbee";
std::string IMUport = "/dev/APM";


//********Communication***********//
int pingRate=10; //nbre de centièmes de secondes entre chaque ping
int lostBeforeEmergency=10; //nbre de ping manqués avant de tout stopper

//********Paramètres eKF**********//
uint16_t eKFTimeRate = 50;

//********Paramètres AutoPilot*******//
uint16_t autoPilotTimeRate = 60; //TODO : voir la valeur avec louis

//*--- For Autopilot Block ---*//

// Target
int MAX_ALTI_TARGET = 2000; //cm
int INI_ALTI_TARGET = 50;//cm
float MAX_PITCH_TARGET = 0.26; //rd
// Roll
float MAX_ROLL_TARGET = 0.26; //rd
// Yaw
float MAX_YAW_TARGET = 2.97; //rd
// Time
int MIN_TIME_RATE = 5; //ms
int INTERP_TIME = 5;//s

// Transfer function boundaries
int EXTREMUM_INTEGRAL_ERROR = 50;

//
// Command boundaries : to be set, depending on the boundaries of motor speed
//
// U1 Altitude limited by maximum acceleration on the drone being 0.5g. Minimum is zero (all motors shutdown)
float MAX_COMMAND_ALTI = 1000.;
float MIN_COMMAND_ALTI = 0.;
// U2 Pitch limited by abs(angle acceleration) < 1
float MAX_COMMAND_PITCH = 0.0081;
float MIN_COMMAND_PITCH = -0.0081;
// U3 Roll limited by abs(angle acceleration) < 1
float MAX_COMMAND_ROLL = 0.0081;
float MIN_COMMAND_ROLL = -0.0081;
// U4 Yaw limited by abs(angle acceleration) < 1
float MAX_COMMAND_YAW = 0.0142;
float MIN_COMMAND_YAW = -0.0142;

// PID constant values
float ALTI_KP = -0.8;
float ALTI_TI = 1.6;
float ALTI_TD = 3.75;

float PITCH_KP  = -3.;
float PITCH_TI = 6.;
float PITCH_TD = 18.;

float ROLL_KP = -3.;
float ROLL_TI = 6.;
float ROLL_TD = 18.;

float YAW_KP = -3.;
float YAW_TI = 6.;
float YAW_TD = 18.;

float K_ARW = -1.;
float N_FILTER = 20.;

// Mechanical constants
float thrust_factor = 0.0000542;
float drag_factor = 0.0000011;
float center_to_motor_distance = 0.24;


// Motors Speed and acceleration bounded
// Computed using physical limitations
// MAX_MOTOR_SPEED : total acceleration inferior to g/2
// MAX_MOTOR_ACCELERATION : no more than 10% of MAX_MOTOR_SPEED can change during min_time_rate

uint16_t motorsTimeRate= 30;

// Last update : #Motors2
float MAX_MOTOR_SPEED = 368.44; // given in rd/s
float MAX_MOTOR_ACCELERATION = 7369.; // given in rd/s^2
float SERVO_MAX_REAL = 1136.;

// Servo port to control motors via ESC
std::string SERVO_PORT = "/dev/servoblaster";

// Times, in microseconds, to control PWM signals
float SERVO_VAL_MIN = 1000.;
float SERVO_VAL_MAX = 2500.;
float SERVO_INIT_PULSE = 1000.;




//********Threads*******//
int mCheckerThread = 0;
int xbeeListenerThread = 1;
int mProcessorThread = 2;
int mSenderThread = 3;
int pingProcessorThread = 4;
int eKFThread = 5;
int autoPilotThread = 6;
int eKFReaderThread = 7;
int motorsThread = 8;

//*******Logging**********//

std::string posLoggingFile= "../Log/position.txt";


//********Paramètres PID*******//

//string messageType[2] = {"SYSTEM","CONTROL", "CONFIG"};


int main()
{
  Drone *d = new Drone();
  d->start();
}
