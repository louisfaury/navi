#ifndef Config_Header_h
#define Config_Header_h

#include<fstream>
#include<string.h>
#include<vector>
#include "Drone.h"
#include "../Com/Message.h"


//---------------------Variables Globales de Configuration--------------------//


//********Fichiers de Config*******//
extern char* config_file;


//********Ports*******//
extern std::string Radio;
extern std::string IMUport;


//********Communication********//
extern int pingRate;
extern int lostBeforeEmergency;

//********EKF*****************//
extern uint16_t eKFTimeRate;

//********Autopilot***********//
extern uint16_t autoPilotTimeRate;


//*--- For Autopilot Block ---*//

// Target
extern int MAX_ALTI_TARGET; //cm
extern int INI_ALTI_TARGET;//cm
extern float MAX_PITCH_TARGET; //rd
// Roll
extern float MAX_ROLL_TARGET; //rd
// Yaw
extern float MAX_YAW_TARGET; //rd
// Time
extern int MIN_TIME_RATE; //ms
extern int INTERP_TIME;//s

// Transfer function boundaries
extern int EXTREMUM_INTEGRAL_ERROR;

//
// Command boundaries : to be set, depending on the boundaries of motor speed
//
// U1 Altitude limited by maximum acceleration on the drone being 0.5g. Minimum is zero (all motors shutdown)
extern float MAX_COMMAND_ALTI;
extern float MIN_COMMAND_ALTI;
// U2 Pitch limited by abs(angle acceleration) < 1
extern float MAX_COMMAND_PITCH;
extern float MIN_COMMAND_PITCH;
// U3 Roll limited by abs(angle acceleration) < 1
extern float MAX_COMMAND_ROLL;
extern float MIN_COMMAND_ROLL;
// U4 Yaw limited by abs(angle acceleration) < 1
extern float MAX_COMMAND_YAW;
extern float MIN_COMMAND_YAW;

// PID constant values
extern float ALTI_KP;
extern float ALTI_TI;
extern float ALTI_TD;

extern float PITCH_KP;
extern float PITCH_TI;
extern float PITCH_TD;

extern float ROLL_KP;
extern float ROLL_TI;
extern float ROLL_TD;

extern float YAW_KP;
extern float YAW_TI;
extern float YAW_TD;

extern float K_ARW;
extern float N_FILTER;

// Mechanical constants
extern float thrust_factor;
extern float drag_factor;
extern float center_to_motor_distance;


// Motors Speed and acceleration bounded
// Computed using physical limitations
// MAX_MOTOR_SPEED : total acceleration inferior to g/2
// MAX_MOTOR_ACCELERATION : no more than 10% of MAX_MOTOR_SPEED can change during min_time_rate

extern uint16_t motorsTimeRate;

// Last update : #Motors2
extern float MAX_MOTOR_SPEED; // given in rd/s
extern float MAX_MOTOR_ACCELERATION; // given in rd/s^2
extern float SERVO_MAX_REAL;

// Servo port to control motors via ESC
extern std::string SERVO_PORT;

// Times, in microseconds, to control PWM signals
extern float SERVO_VAL_MIN;
extern float SERVO_VAL_MAX;
extern float SERVO_INIT_PULSE;


//********Motors*************//
extern uint16_t motorsTimeRate;

//********Threads*******//
extern int mCheckerThread;
extern int xbeeListenerThread;
extern int mProcessorThread;
extern int mSenderThread;
extern int pingProcessorThread;
extern int eKFThread;
extern int autoPilotThread;
extern int eKFReaderThread;
extern int motorsThread;

//********Paramètres PID*******//




//********classe config********//

class Drone;

class Config{
  
public:
  
  static int read_config(Drone* drone);
  
  static int write_config();
  
  static int modify(char* parameter, char* value);
  
  static void interpret_line(std::string line,Drone* drone_);
  
  static void decompose(std::string* msg, std::string delimiter, std::vector<std::string> * vect);
  
  Config(){};
  
  ~Config();
  
};


#endif
