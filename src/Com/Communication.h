#ifndef Communication_Header_h
#define Communication_Header_h

#include<exception>

#include "../Utils/BlockingQueue.h"
#include "MessageChecker.h"
#include "../Utils/Listener.h"
#include <string>

#include "../Drone/Drone.h"
#include "Message.h"
#include "MessageProcessor.h"
#include "MessageSender.h"
#include "PingProcessor.h"
#include "ComException.h"

#include "../Navi_Exception/INS_Exception.hpp"
#include "../Navi_Exception/Pilot_Exception.hpp"
#include "../Navi_Exception/System_Exception.hpp"
#include "../Navi_Exception/serial_exception.hpp"
#include "../Navi_Exception/Motor_Exception.hpp"




extern std::string Radio;

class Drone;
class MessageChecker;
class MessageProcessor;
class MessageSender;
class PingProcessor;
class ComException;


class Communication{
  
public :
  
  Communication(Drone* drone_);
  ~Communication();
  void start();
  void stop();
  
  char* rMsgPop();
  Message* ttMsgPop();
  void addttMsg(Message* msg);
  void addtsMsg(Message* msg);
  Message* tsMsgPop();
  char* pingPop();
  
  void sendStr(char* str);
  
  void registerAnswer(int id);
  
  
 //********Envoi des exceptions*******//
  
  void launchException(INS_Exception e);
  void launchException(Pilot_Exception e);
  void launchException(System_Exception e);
  void launchException(serial_exception e);
  void launchException(ComException e);
  void launchException(Motor_Exception e);
  
    
    
private :
  
  Drone* drone;
  
  BlockingQueue<char*>* rMsg;
  BlockingQueue<Message*>* tsMsg;
  BlockingQueue<Message*>* ttMsg;
  BlockingQueue<char*>* ping;
  
  MessageChecker* rMsgChecker; 
  MessageSender* msgSender;
  
  Listener* rMsgListener;
  
  MessageProcessor* msgProcessor;
  PingProcessor* pingProcessor;
  
  
  
};
#endif
