
#include "PingProcessor.h"


PingProcessor::PingProcessor(Communication* moduleCom_, Drone* drone_): moduleCom(moduleCom_), drone(drone_) {
  id = new int(1);
  for(int k = 0; k<lostBeforeEmergency; k++){
    waiting[k]=-1;
  }
    
    pos = drone->getPos();
    target = drone->getTarget();
    speed = drone->getSpeed();
    angles = drone->getAngles();
    charge = drone->getCharge();
    posincr = drone->getPosIncr();
    speedincr = drone->getSpeedIncr();
    angleincr = drone->getAngleIncr();
    chargeincr = drone->getChargeIncr();
    
    alt = drone->getAlt();
    altincr = drone->getAltIncr();

    home_given = false;
    
}

PingProcessor::~PingProcessor(){
  delete drone;
  delete moduleCom;
  delete [] waiting;
}

void PingProcessor::start(){
  drone->startThread(this, pingProcessorThread);
  //Message* msg = new Message(Message::SYSTEM, "pingProcessor", 0);
  //moduleCom->addtsMsg(msg);
  
}


void* PingProcessor::run(){
    int i = 0;
    //régler le paramètre i adéquat
  while(true){
      if(i==0){
          std::stringstream ss;
          ss<<*id;
          ss<<";r;";
          ss<<pos->getX();
          ss<<";";
          ss<<pos->getY();
          ss<<";";
          ss<<pos->getZ();
          ss<<";";
          ss<<*alt;
          ss<<";";
          ss<<speed->getX();
          ss<<";";
          ss<<speed->getY();
          ss<<";";
          ss<<speed->getZ();
          ss<<";";
          ss<<angles->getX();
          ss<<";";
          ss<<angles->getY();
          ss<<";";
          ss<<angles->getZ();
          ss<<";";
          ss<<*charge;
	  ss<<";";
          std::string message = ss.str();
          Message* msg = new Message(Message::PING, message, 0);
          moduleCom->addtsMsg(msg);
          waitAnswer(*id);
          *id = *id+1;
          usleep(pingRate*10000);
      //i++;
      }else{
          std::stringstream ss;
          ss<<*id;
          ss<<";i;";
          ss<<posincr->getX();
          ss<<";";
          ss<<posincr->getY();
          ss<<";";
          ss<<posincr->getZ();
          ss<<";";
          ss<<*altincr;
          ss<<";";
          ss<<speedincr->getX();
          ss<<";";
          ss<<speedincr->getY();
          ss<<";";
          ss<<speedincr->getZ();
          ss<<";";
          ss<<angleincr->getX();
          ss<<";";
          ss<<angleincr->getY();
          ss<<";";
          ss<<angleincr->getZ();
          ss<<";";
          ss<<*chargeincr;
	  ss<<";";
          std::string message = ss.str();
          Message* msg = new Message(Message::PING, message, 0);
          moduleCom->addtsMsg(msg);
          waitAnswer(*id);
          *id = *id+1;
          usleep(pingRate*10000);
	  if(i<10){
	    i++;
	  }else{
	    i=0;
	  }

      }
  }
  sendHome();
  return 0;
}

void PingProcessor::waitAnswer(int i){
  
  pthread_mutex_lock(&waiting_mutex);
  for(int k =0; k<lostBeforeEmergency; k++){
    if(waiting[k] == -1){
      waiting[k] = i;
      pthread_mutex_unlock(&waiting_mutex);
      return; 
    }
  }
  pthread_mutex_unlock(&waiting_mutex);
  std::cout<<"Communication lost, emergency stop !"<< std::endl;
}

void PingProcessor::registerAnswer(int i){
  for(int k = 0; k<lostBeforeEmergency; k++){
    if(waiting[k]<=i){
      waiting[k] = -1;
    }
  }
}

void PingProcessor::sendHome(){
    if(!drone->isHomeGiven()){
        std::string delimiter = std::string(";");
        moduleCom->addtsMsg(new Message(Message::HOME, std::to_string(drone->getHome()->getX()) + delimiter + std::to_string(drone->getHome()->getX()) + delimiter+ std::to_string(drone->getHome()->getX()) + delimiter,
                            1));
    }
}
