#include "Communication.h"



using namespace std;

Communication::Communication(Drone* drone_): drone(drone_){
  
  rMsg = new BlockingQueue<char*>();
  tsMsg = new BlockingQueue<Message*>();
  ttMsg = new BlockingQueue<Message*>();
  
      std::cout<<Radio<<std::endl;
  rMsgListener = new Listener((char*)Radio.c_str(), rMsg, 115200);
  rMsgChecker = new MessageChecker(this, drone);
  msgProcessor = new MessageProcessor(this,drone);
  msgSender = new MessageSender(this,drone);
  pingProcessor = new PingProcessor(this, drone);
  
  
}

Communication::~Communication(){
    delete drone;
    delete ttMsg;
    delete tsMsg;
    delete rMsg;
    delete ping;
    delete rMsgChecker;
    delete msgSender;
    delete rMsgListener;
    delete msgProcessor;
    delete pingProcessor;
}

void Communication::start(){
  
  rMsgListener->start();
  rMsgChecker->start();
  msgProcessor->start();
  msgSender->start();
  pingProcessor->start();
   
  std::cout<<"Communication started"<<std::endl;
    
}

char* Communication::rMsgPop(){

  return rMsg->pop();
  
}

Message* Communication::ttMsgPop(){
  //std::cout<<"okttmsg"<<std::endl;
  return ttMsg->pop();
}

void Communication::addttMsg(Message* msg){
  //std::cout<<"okaddmsg"<<std::endl;
  ttMsg->add(msg);
}


Message* Communication::tsMsgPop(){
  //std::cout<<"okttmsg"<<std::endl;
  return tsMsg->pop();
}

void Communication::addtsMsg(Message* msg){
  tsMsg->add(msg);
}

void Communication::sendStr(char* str){
  rMsgListener->write(str);
}

void Communication::registerAnswer(int id){
  pingProcessor->registerAnswer(id);
}

void Communication::launchException(ComException e){
    Message* msg = new Message(Message::EXCEPTION, e.what(), 0);
    std::cout<<e.what()<<std::endl;
    addtsMsg(msg);
}

void Communication::launchException(INS_Exception e){
    Message* msg = new Message(Message::EXCEPTION, e.what(), 0);
    std::cout<<e.what()<<std::endl;
    addtsMsg(msg);
}

void Communication::launchException(Pilot_Exception e){
    Message* msg = new Message(Message::EXCEPTION, e.what(), 0);
    std::cout<<e.what()<<std::endl;
    addtsMsg(msg);
}

void Communication::launchException(System_Exception e){
    Message* msg = new Message(Message::EXCEPTION, e.what(), 0);
    std::cout<<e.what()<<std::endl;
    addtsMsg(msg);
}

void Communication::launchException(serial_exception e){
    Message* msg = new Message(Message::EXCEPTION, e.what(), 0);
    std::cout<<e.what()<<std::endl;
    addtsMsg(msg);
}

void Communication::launchException(Motor_Exception e){
    Message* msg = new Message(Message::EXCEPTION, e.what(), 0);
    std::cout<<e.what()<<std::endl;
    addtsMsg(msg);
}
