
#include "Drone.h"


extern int autoPilotThread;

Drone::Drone(){
  
  target =  new Point3D<int>(0, 0, 0);
  pos =  new Point3D<int>(0,0,0);
  angles =  new Point3D<int>(0,0,0);
  speed =  new Point3D<int>(0,0,0);
  posincr =  new Point3D<int>(0,0,0);
  angleincr =  new Point3D<int>(0, 0, 0);
  speedincr =  new Point3D<int>(0, 0, 0);
  alt = new int(0);
  charge = new int(0);
  altincr = new int(0);
  chargeincr = new int(0);
  home = new Point3D<double>(0,0,0);

  home_given = true;
  new_command= false;
    
  pthread_mutex_init(&m_mutex, NULL);
  pthread_cond_init(&m_condv, NULL);
  
  pthread_mutex_init(&alt_mutex, NULL);
  pthread_mutex_init(&altincr_mutex, NULL);

  pthread_mutex_init(&charge_mutex, NULL);
  pthread_mutex_init(&chargeincr_mutex, NULL);
  
  pthread_mutex_init(&home_given_mutex, NULL);

  pthread_mutex_init(&commands_mutex, NULL);
  
  threadList[0]=new ThreadStruct("mpr",2,1,Thread::FIFO);
  threadList[1]=new ThreadStruct("xbee",2,1,Thread::FIFO);
  threadList[2]=new ThreadStruct("mProcessor",2,1,Thread::FIFO);
  threadList[3]=new ThreadStruct("mSender",2,1,Thread::FIFO);
  threadList[4]=new ThreadStruct("pingProcessor",2,1,Thread::FIFO);
  threadList[5]=new ThreadStruct("eKF", 2, 1, Thread::FIFO);
  threadList[6]=new ThreadStruct("autoPilot", 2, 1, Thread::FIFO);
  threadList[7]=new ThreadStruct("eKFReader",2,1,Thread::FIFO);
  threadList[8]=new ThreadStruct("motors",2,1,Thread::FIFO);


}

Drone::~Drone(){}


void Drone::start(){
  

  startCom();

  std::cout<<"Drone initialized, reading config"<<std::endl;
  Config::read_config(this);

  sleep(1);
  std::cout<<"Drone configured, lauching modules"<<std::endl;

  sendMsg(new Message(Message::SYSTEM,"Drone desormais configure;",1));

  //pour ne pas engorger la com
  sleep(5);
  startEKF();
  sendMsg(new Message(Message::SYSTEM, "Module EKF initialise;",1));
  sleep(1);
  //startAutoPilot();
  //sendMsg(new Message(Message::SYSTEM, "Module autoPilot initialise;",1));
  //sleep(1);
  //startMaestroMotor();
  //sendMsg(new Message(Message::SYSTEM, "Module maestro motors initialise;",1));
  
  sendMsg(new Message(Message::SYSTEM, "Le drone est desormais initialise;",1));
  
  pthread_mutex_lock(&m_mutex);
  pthread_cond_wait(&m_condv, &m_mutex);
  pthread_mutex_unlock(&m_mutex);
  std::cout <<"killing"<<std::endl;
  
}

void Drone::startCom(){
    moduleCom = new Communication(this);
    moduleCom->start();
    
}


void Drone::startAutoPilot(){
    //TODO : ajouter un controle déjà starté
    pilot = new Autopilot(this);
    pilot->start();
}

void Drone::startEKF(){
    moduleEKF = new EKF(this); //attendre que le constructeur soit modifié
    moduleEKF->start();
}

void Drone::startIMU(){
    if(moduleEKF->isLaunched()){
       sendMsg(new Message(Message::SYSTEM,"Erreur : l'IMU est deja en train de debiter;",1));
    }
    else{
        moduleEKF->set_launching_order();
        sendMsg(new Message(Message::SYSTEM,"Attention l'IMU va demarrer;",1));
    }

}

void Drone::startMaestroMotor(){
    motors= new MaestroMotor(this);
    motors->start();
}

void Drone::startThread(Runnable* runnable, int id){
  threadList[id]->start(runnable);
}


void Drone::shutOff(){
  pthread_mutex_lock(&m_mutex);
  pthread_cond_signal(&m_condv);
  pthread_mutex_unlock(&m_mutex);
}


void Drone::land(){
 //#Louis
  if(pilot->getTookOff()){
    pilot->land();
    sendMsg(new Message(Message::SYSTEM,"Procedure d'atterissage lancee;",1));
  }else{
      sendMsg(new Message(Message::SYSTEM,"Le drone n'a pas decolle !;",1));
  }
}

void Drone::take_off(){
  //#Louis
    if(!pilot->getTookOff()){
      motors->launch();
      pilot->take_off();
      sendMsg(new Message(Message::SYSTEM,"Procedure de decollage lancee;",1));
    }else{
        sendMsg(new Message(Message::SYSTEM,"Le drone est deja en l'air!;",1));
    }
}

void Drone::calibrIMU(){
  //#Louis
    if(moduleEKF->isCalibrated()){
        sendMsg(new Message(Message::SYSTEM,"Erreur : l'IMU est deja calibree;",1));
    }
    else{
        std::cout<<"drone good"<<std::endl;
        moduleEKF->set_calibrating_order();
        std::cout<<"drone order transmitted"<<std::endl;
        sendMsg(new Message(Message::SYSTEM,"Attention la calibration va commencer;",1));
    }
}


void Drone::startAll(){
  //TODO
  /*if(){
    sendMsg(new Message(Message::SYSTEM,"StartAll impossible, IMU non calibrée;",1));
  }*/
}

void Drone::stopAll(){
  //TODO
}

void Drone::stopIMU(){
  //TODO
}

void Drone::stopPilot(){
  //TODO
}

void Drone::EmergencyStop(){
  //TODO #Louis
    motors->shutdown();
    sendMsg(new Message(Message::SYSTEM,"Shutdown : ordre donné aux moteurs;",1));
}



bool Drone::isHomeGiven(){
    bool result;
    pthread_mutex_lock(&home_given_mutex);
    result = home_given;
    pthread_mutex_unlock(&home_given_mutex);
}

void Drone::setHomeGiven(bool is){
    pthread_mutex_lock(&home_given_mutex);
    home_given = is;
    pthread_mutex_unlock(&home_given_mutex);
}

int* Drone::getComId(){
  return new int(0);
}


Point3D<int>* Drone::getPos(){
    return pos;
}

Point3D<int>* Drone::getSpeed(){
    return speed;
}

Point3D<int>* Drone::getTarget(){
    return target;
}

Point3D<int>* Drone::getAngles(){
    return angles;
}


Point3D<int>* Drone::getPosIncr(){
    return posincr;
}

Point3D<int>* Drone::getSpeedIncr(){
    return speedincr;
}


Point3D<int>* Drone::getAngleIncr(){
    return angleincr;
}

Point3D<double>* Drone::getHome(){
    return home;
}


int* Drone::getAlt(){
    pthread_mutex_lock(&alt_mutex);
    int* r = alt;
    pthread_mutex_unlock(&alt_mutex);
    return r;
}

int* Drone::getCharge(){
    pthread_mutex_lock(&charge_mutex);
    int* r = charge;
    pthread_mutex_unlock(&charge_mutex);
    return r;
}

int* Drone::getAltIncr(){
    pthread_mutex_lock(&altincr_mutex);
    int* r = altincr;
    pthread_mutex_unlock(&altincr_mutex);
    return r;
}

int* Drone::getChargeIncr(){
    pthread_mutex_lock(&chargeincr_mutex);
    int* r = chargeincr;
    pthread_mutex_unlock(&chargeincr_mutex);
    return r;
}

void Drone::setHome(std::vector<double> vect){
    double x = vect[0];
    double y = vect[1];
    double z = vect[2];
    home->setX(x);
    home->setY(y);
    home->setZ(z);
    setHomeGiven(false);
}

void Drone::setPos(int x, int y, int z){
    setPosIncr(x-getPos()->getX(), y-getPos()->getY(), z-getPos()->getZ());
    pos->setX(x);
    pos->setY(y);
    pos->setZ(z);
}

void Drone::setTarget(int x, int y, int z){
    //update target de l'autopilot
    //TODO

    //update target de la classe drone
    target->setX(x);
    target->setY(y);
    target->setZ(z);
    pilot->setAltitudeTarget(z);
    std::string delimiter = std::string(";");
    sendMsg(new Message(Message::TARGET,std::to_string(x) + delimiter + std::to_string(y) + delimiter + std::to_string(z)+delimiter,1));
}

void Drone::setAnglesTarget(int a, int b, int c){
    anglestarget->setX(a);
    anglestarget->setY(b);
    anglestarget->setZ(c);
    pilot->setRollTarget(a);
    pilot->setPitchTarget(b);
    pilot->setYawTarget(c);

}

void Drone::setSpeed(int vx, int vy, int vz){
    setSpeedIncr(vx-getSpeed()->getX(), vy-getSpeed()->getY(),vz-getSpeed()->getZ());
    speed->setX(vx);
    speed->setY(vy);
    speed->setZ(vz);
}

void Drone::setAngles(int a, int b, int c){
    setAngleIncr(a-getAngles()->getX(), b-getAngles()->getY(), c-getAngles()->getZ());
    angles->setX(a);
    angles->setY(b);
    angles->setZ(c);
}

void Drone::setAlt(int z){
    setAltIncr(z-*getAlt());
    pthread_mutex_lock(&alt_mutex);
    *alt = z;
    pthread_mutex_unlock(&alt_mutex);
}

void Drone::setCharge(int c){
    setChargeIncr(c-*getCharge());
    pthread_mutex_lock(&charge_mutex);
    *charge = c;
    pthread_mutex_unlock(&charge_mutex);
}


void Drone::setPosIncr(int x, int y, int z){
    posincr->setX(x);
    posincr->setY(y);
    posincr->setZ(z);
}


void Drone::setSpeedIncr(int vx, int vy, int vz){
    speedincr->setX(vx);
    speedincr->setY(vy);
    speedincr->setZ(vz);
}

void Drone::setAngleIncr(int a, int b, int c){
    angleincr->setX(a);
    angleincr->setY(b);
    angleincr->setZ(c);
}

void Drone::setAltIncr(int z){
    pthread_mutex_lock(&altincr_mutex);
    *altincr = z;
    pthread_mutex_unlock(&altincr_mutex);
}

void Drone::setChargeIncr(int c){
    pthread_mutex_lock(&chargeincr_mutex);
    *chargeincr = c;
    pthread_mutex_unlock(&chargeincr_mutex);
}

void Drone::setCommands(float alti, float pitch, float roll, float yaw){
    pthread_mutex_lock(&commands_mutex);
    commands[0]=alti;
    commands[1]=pitch;
    commands[2]=roll;
    commands[3]=yaw;
    new_command = true;
    pthread_cond_signal(&commands_mutex_condv);
    pthread_mutex_unlock(&commands_mutex);


}

Eigen::Vector4f Drone::getCommands(){
    Eigen::Vector4f result;
    pthread_mutex_lock(&commands_mutex);
    if(new_command){
        result[0] = commands[0];
        result[1] = commands[1];
        result[2] = commands[2];
        result[3] = commands[3];
        new_command= false;
    }else{
        pthread_cond_wait(&commands_mutex_condv, &commands_mutex);
        result[0] = commands[0];
        result[1] = commands[1];
        result[2] = commands[2];
        result[3] = commands[3];
        new_command = false;
    }
    pthread_mutex_unlock(&commands_mutex);
    return result;
}

void Drone::sendMsg(Message* msg){
    moduleCom->addtsMsg(msg);
}

//********Envoi des exceptions*******//
    
void Drone::launchException(INS_Exception e){
  moduleCom->launchException(e);
}


void Drone::launchException(Pilot_Exception e){
  moduleCom->launchException(e);
}


void Drone::launchException(System_Exception e){
  moduleCom->launchException(e);
}

void Drone::launchException(serial_exception e){

  moduleCom->launchException(e);
}

void Drone::launchException(Motor_Exception e){

  moduleCom->launchException(e);
}

void Drone::log(){
    std::ofstream file;
    file.open("position.txt", std::ios::app);
    if(file.is_open()){
        file<<getPos()->getX() << "\t" << getPos()->getY() << "\t" << getPos()->getZ() << "\t" << *getAlt() << "\t" <<
              getSpeed()->getX() << "\t" << getSpeed()->getY() << "\t" << getSpeed()->getZ() << "\t" <<
              getAngles()->getX() << "\t" << getAngles()->getY() << "\t" <<getAngles()->getZ() << "\n" ;
        file.close();
    }


}
