#ifndef Drone_Header_h
#define Drone_Header_h

#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include "../../lib/Eigen/Eigen/Dense"

#include "../Thread/ThreadStruct.h"
#include "../Com/Communication.h"
#include "../Utils/Point3D.hpp"
#include "../Com/Message.h"
#include "../AutoPilot/Autopilot.hpp"
#include "../INS_EKF/EKF.h"
#include "Config.h"
#include "../Utils/Listener.h"
#include "../Thread/Thread.h"
#include "../Utils/BlockingQueue.h"
#include "../Com/MessageChecker.h"
#include "../Utils/Point3D.hpp"
#include "../MaestroMotor/MaestroMotor.hpp"

#include "../Navi_Exception/INS_Exception.hpp"
#include "../Navi_Exception/Pilot_Exception.hpp"
#include "../Navi_Exception/System_Exception.hpp"
#include "../Navi_Exception/serial_exception.hpp"
#include "../Navi_Exception/Motor_Exception.hpp"

//********variables globales*********//

extern std::string posLoggingFile;


//--------------------Code du Drone-------------------------------------------//


class Communication;
class IMU;
class EKF;
class Autopilot;
class MaestroMotor;

class Drone {
  
  
  public:
    
    Drone();
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    ~Drone();
    
//********Fonctions d'initialisation*******//
    void start();
    void startCom();
    void startAutoPilot();
    void startEKF();


    void startMaestroMotor();
    
    void readConfig();
    void readThreadConfig();
    
    
    void startThread(Runnable* runnable, int id);


//********Fonctions "carrefours" entre modules*******//
    void sendMsg(Message* msg);
 

//********Actions définies*******//
    void shutOff();
    void land();
    void take_off();
    int* getComId();
    void calibrIMU();
    void startAll();
    void startIMU();
    void stopIMU();
    void stopPilot();
    void stopAll();
    void EmergencyStop();
    void startMotors();
//********Actions de l'autopilot sur les moteurs********//

    void setCommands(float,float,float,float);


    Eigen::Vector4f getCommands();

    //TODO
    void motorsShutdown();

//********Modification de la config*******//
    //void changeConfig(char[] change)

//********Accès/modification des paramètres d'état*******//
    Point3D<int>* getPos();
    Point3D<int>* getSpeed();
    Point3D<int>* getTarget();
    Point3D<int>* getAnglesTarget();
    Point3D<int>* getAngles();
    Point3D<int>* getPosIncr();
    Point3D<int>* getSpeedIncr();
    Point3D<int>* getAngleIncr();
    int* getAlt();
    int* getAltIncr();
    int* getCharge();
    int* getChargeIncr();
  
    Point3D<double>* getHome();

    void setPos(int x, int y, int z);
    void setTarget(int x, int y, int z);
    void setAnglesTarget(int a, int b, int c);
    void setSpeed(int vx, int vy, int vz);
    void setAngles(int a, int b, int c);
    void setAlt(int z);
    void setPosIncr(int x, int y, int z);
    void setSpeedIncr(int vx, int vy, int vz);
    void setAngleIncr(int a, int b, int c);
    void setAltIncr(int z);
    void setCharge(int c);
    void setChargeIncr(int c);

    void setHome(std::vector<double>);
    
    
//********Envoi des exceptions*******//
    
    void launchException(INS_Exception e);
    void launchException(Pilot_Exception e);
    void launchException(System_Exception e);
    void launchException(serial_exception e);
    void launchException(Motor_Exception e);

//********Gestion de l'origine du repère*******//
    void setHomeGiven(bool is);

    bool isHomeGiven();


//********log trajectory***********//

    void log();

/*******************************************************/
    
  private:
    
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_condv;
    
    

    ThreadStruct* threadList[20];
    
//********Modules*******//
    Communication* moduleCom;
    IMU* moduleIMU;
    Autopilot* pilot;
    EKF* moduleEKF;
    MaestroMotor* motors;
 

    
//********Paramètres d'état*******//
    Point3D<int>* target;
    Point3D<int>* anglestarget;
    Point3D<int>* pos;
    Point3D<int>* speed;
    Point3D<int>* angles;
    Point3D<int>* posincr;
    Point3D<int>* speedincr;
    Point3D<int>* angleincr;
    Point3D<double>* home;

    pthread_mutex_t alt_mutex;
    int* alt;
    pthread_mutex_t altincr_mutex;
    int* altincr;
    
    pthread_mutex_t charge_mutex;
    int* charge;
    pthread_mutex_t chargeincr_mutex;
    int* chargeincr;


//********Gestion de l'origine du repère*******//
    bool home_given;
    pthread_mutex_t home_given_mutex;


//*******Gestion des commandes moteurs*********//
    Eigen::Vector4f commands;
    pthread_mutex_t commands_mutex;
    pthread_cond_t  commands_mutex_condv;
    bool new_command;
};

#endif

  
