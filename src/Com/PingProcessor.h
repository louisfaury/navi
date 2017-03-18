#ifndef PingProcessor_Header_h
#define PingProcessor_Header_h

#include <string>
#include<sstream>
#include<iostream>
#include <pthread.h>

#include "../Thread/Runnable.h"
#include "Message.h"
#include "../Drone/Drone.h"
#include "Communication.h"
#include "../Utils/Point3D.hpp"
#include "Communication.h"

extern int pingProcessorThread;
extern int pingRate;
extern int lostBeforeEmergency;



class Communication;
class Drone;


class PingProcessor : public Runnable {
  
public:
  
  PingProcessor(Communication* moduleCom_, Drone* drone_);
  ~PingProcessor();
  
  void start();
  void* run();
  
  void registerAnswer(int i);

  void sendHome();
  
private:
  
  Drone* drone;
  Communication* moduleCom;
  int* id;
    
  Point3D<int>* target;
  Point3D<int>* pos;
  Point3D<int>* speed;
  Point3D<int>* angles;
  Point3D<int>* posincr;
  Point3D<int>* speedincr;
  Point3D<int>* angleincr;
    
    
    //Attention : les verrous de la classe drone ne servent a rien ici
  int* alt;
  int* altincr;
  int* charge;
  int* chargeincr;
    
    
  
  
  void waitAnswer(int i);
  
  pthread_mutex_t waiting_mutex;
  int* waiting = new int[lostBeforeEmergency];

  bool home_given;
  
  
  
  
};
#endif
