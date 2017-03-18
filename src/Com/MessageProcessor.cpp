#include "MessageProcessor.h"



MessageProcessor::MessageProcessor(Communication* moduleCom_, Drone* drone_): moduleCom(moduleCom_), drone(drone_){}

MessageProcessor::~MessageProcessor(){}

void MessageProcessor::start(){
  drone->startThread(this, mProcessorThread);
}

void* MessageProcessor::run(){
    while(true){
        Message * msg= moduleCom->ttMsgPop();
        treatMsg(msg);
	delete msg;
    }
    return 0;
}

void MessageProcessor::decompose(std::string* msg, std::string delimiter, std::vector<std::string> * vect){
  std::size_t pos = 1;
  std::size_t oldpos = 0;
  std::string param;
  pos = msg->find(delimiter);
  if(pos==std::string::npos){
    vect->push_back(*msg);
  }else{
    while(pos < std::string::npos){
      param = msg->substr(oldpos, pos-oldpos);
      vect->push_back(param);
      oldpos = pos+1;
      pos = msg->find(delimiter, oldpos);
    }
  }
  
}


void MessageProcessor::treatMsg(Message* msg){
    std::string* content =msg->getContent();
    if(msg->getType()==Message::CONFIG){
      //TODO : à tester et lancer une réponse SYSTEM.
      //TODO : créer un message getConfig depuis l'ordi auquel le drone répondrait sa config.
        Config::interpret_line(*content, drone);
        Config::write_config();
    }else{
    
      std::vector<std::string> vect;
      std::string delimiter = ";";
      
      decompose(content, delimiter, &vect);
      
      
      
      //--------------DRONE--------------------//
      if(msg->getType()==Message::SYSTEM){
        if(!vect[0].compare("kill")){
          drone->shutOff();
        }
        if(!vect[0].compare("startIMU")){
          drone->startIMU();
        }
        if(!vect[0].compare("startPilot")){
          drone->startAutoPilot();
        }
        if(!vect[0].compare("startAll")){
          drone->startAll();
        }
        if(!vect[0].compare("calibrIMU")){
            std::cout<<"Message processor : calibration de l'IMU"<<std::endl;
          drone->calibrIMU();
        }
        if(!vect[0].compare("stopIMU")){
          drone->stopIMU();
        }
        if(!vect[0].compare("stopPilot")){
          drone->stopPilot();
        }
        if(!vect[0].compare("stopAll")){
          drone->stopAll();
        }
        if(!vect[0].compare("emergencyStop")){
          drone->EmergencyStop();
        }

      }
      if(msg->getType()==Message::PINGANSWER){
          int id = atoi(vect[0].c_str());
          moduleCom->registerAnswer(id);
      }
    
      if(msg->getType()== Message::TARGET){
            drone->setTarget(::atoi(vect[0].c_str()),::atoi(vect[1].c_str()), atoi(vect[2].c_str()));
            drone->setAnglesTarget(::atoi(vect[3].c_str()),::atoi(vect[4].c_str()), atoi(vect[5].c_str()));
      }

      if(msg->getType()== Message::HOME){
        if(homeCheck(std::stod(vect[0]),std::stod(vect[1]),std::stod(vect[2]))){
            drone->setHomeGiven(true);
        }
      }
    }

}

bool MessageProcessor::homeCheck(double x, double y, double z){
    if((x==(drone->getHome()->getX()))&&(y==(drone->getHome()->getY()))&&(z==(drone->getHome()->getZ()))){
        return true;
    }
    else{
        return false;
    }
}
