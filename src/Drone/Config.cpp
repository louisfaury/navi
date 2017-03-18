#include "Config.h"
#include <iostream>

int Config::read_config(Drone* drone){
  
  std::ifstream file(config_file, std::ios::in);
  if(file){
    std::string line;
    while(getline(file, line)){
      Config::interpret_line(line, drone);
    }
    file.close();
    return 1;
  }
  else return 0;
  
}

void Config::interpret_line(std::string line, Drone* drone){
  std::vector<std::string> vect;
  std::string delimiter(";");
  Config::decompose(&line, delimiter, &vect);
  
  if(vect[0].compare("Radioport")==0){
    Radio = vect[1];
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("Radioport ")+std::string("set to ")+std::string(Radio)+';',1));
  }
  if(vect[0].compare("IMUport")==0){
    IMUport = vect[1];
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("IMUport ")+std::string("set to ")+std::string(IMUport)+';',1));
  }
  if(vect[0].compare("pingRate")==0){
    pingRate= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("pingRate ")+std::string("set to ")+std::to_string(pingRate)+';',1));
  }
  if(vect[0].compare("lostBeforeEmergency")==0){
    lostBeforeEmergency= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("lostBeforeEmergency ")+std::string("set to ")+std::to_string(lostBeforeEmergency)+';',1));
  }
  if(vect[0].compare("eKFTimeRate")==0){
    eKFTimeRate= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("eKFTimeRate ")+std::string("set to ")+std::to_string(eKFTimeRate)+';',1));
  }
  if(vect[0].compare("autoPilotTimeRate")==0){
    autoPilotTimeRate= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("autoPilotTimeRate ")+std::string("set to ")+std::to_string(autoPilotTimeRate)+';',1));
  }
  if(vect[0].compare("MAX_ALTI_TARGET")==0){
    MAX_ALTI_TARGET= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MAX_ALTI_TARGET ")+std::string("set to ")+std::to_string(MAX_ALTI_TARGET)+';',1));
  }
  if(vect[0].compare("INI_ALTI_TARGET")==0){
    INI_ALTI_TARGET= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("INI_ALTI_TARGET ")+std::string("set to ")+std::to_string(INI_ALTI_TARGET)+';',1));
  }
  if(vect[0].compare("MAX_PITCH_TARGET")==0){
    MAX_PITCH_TARGET= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MAX_PITCH_TARGET ")+std::string("set to ")+std::to_string(MAX_PITCH_TARGET)+';',1));
  }
  if(vect[0].compare("MAX_ROLL_TARGET")==0){
    MAX_ROLL_TARGET= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MAX_ROLL_TARGET ")+std::string("set to ")+std::to_string(MAX_ROLL_TARGET)+';',1));
  }
  if(vect[0].compare("MAX_YAW_TARGET")==0){
    MAX_YAW_TARGET= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MAX_YAW_TARGET ")+std::string("set to ")+std::to_string(MAX_YAW_TARGET)+';',1));
  }
  if(vect[0].compare("MIN_TIME_RATE")==0){
    MIN_TIME_RATE= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MIN_TIME_RATE ")+std::string("set to ")+std::to_string(MIN_TIME_RATE)+';',1));
  }
  if(vect[0].compare("INTERP_TIME")==0){
    INTERP_TIME= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("INTERP_TIME ")+std::string("set to ")+std::to_string(INTERP_TIME)+';',1));
  }
  if(vect[0].compare("EXTREMUM_INTEGRAL_ERROR")==0){
    EXTREMUM_INTEGRAL_ERROR= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("EXTREMUM_INTEGRAL_ERROR ")+std::string("set to ")+std::to_string(EXTREMUM_INTEGRAL_ERROR)+';',1));
  }
  if(vect[0].compare("MAX_COMMAND_ALTI")==0){
    MAX_COMMAND_ALTI= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MAX_COMMAND_ALTI ")+std::string("set to ")+std::to_string(MAX_COMMAND_ALTI)+';',1));
  }
  if(vect[0].compare("MIN_COMMAND_ALTI")==0){
    MIN_COMMAND_ALTI= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MIN_COMMAND_ALTI ")+std::string("set to ")+std::to_string(MIN_COMMAND_ALTI)+';',1));
  }
  if(vect[0].compare("MAX_COMMAND_PITCH")==0){
    MAX_COMMAND_PITCH= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MAX_COMMAND_PITCH ")+std::string("set to ")+std::to_string(MAX_COMMAND_PITCH)+';',1));
  }
  if(vect[0].compare("MIN_COMMAND_PITCH")==0){
    MIN_COMMAND_PITCH= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MIN_COMMAND_PITCH ")+std::string("set to ")+std::to_string(MIN_COMMAND_PITCH)+';',1));
  }
  if(vect[0].compare("MAX_COMMAND_ROLL")==0){
    MAX_COMMAND_ROLL= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MAX_COMMAND_ROLL ")+std::string("set to ")+std::to_string(MAX_COMMAND_ROLL)+';',1));
  }
  if(vect[0].compare("MIN_COMMAND_ROLL")==0){
    MIN_COMMAND_ROLL= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MIN_COMMAND_ROLL ")+std::string("set to ")+std::to_string(MIN_COMMAND_ROLL)+';',1));
  }
  if(vect[0].compare("MAX_COMMAND_YAW")==0){
    MAX_COMMAND_YAW= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MAX_COMMAND_YAW ")+std::string("set to ")+std::to_string(MAX_COMMAND_YAW)+';',1));
  }
  if(vect[0].compare("MIN_COMMAND_YAW")==0){
    MIN_COMMAND_YAW= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MIN_COMMAND_YAW ")+std::string("set to ")+std::to_string(MIN_COMMAND_YAW)+';',1));
  }
  if(vect[0].compare("ALTI_KP")==0){
    ALTI_KP= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("ALTI_KP ")+std::string("set to ")+std::to_string(ALTI_KP)+';',1));
  }
  if(vect[0].compare("ALTI_TI")==0){
    ALTI_TI= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("ALTI_TI ")+std::string("set to ")+std::to_string(ALTI_TI)+';',1));
  }
  if(vect[0].compare("ALTI_TD")==0){
    ALTI_TD= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("ALTI_TD ")+std::string("set to ")+std::to_string(ALTI_TD)+';',1));
  }
  if(vect[0].compare("PITCH_KP")==0){
    PITCH_KP= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("PITCH_KP ")+std::string("set to ")+std::to_string(PITCH_KP)+';',1));
  }
  if(vect[0].compare("PITCH_TI")==0){
    PITCH_TI= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("PITCH_TI ")+std::string("set to ")+std::to_string(PITCH_TI)+';',1));
  }
  if(vect[0].compare("PITCH_TD")==0){
    PITCH_TD= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("PITCH_TD ")+std::string("set to ")+std::to_string(PITCH_TD)+';',1));
  }
  if(vect[0].compare("ROLL_KP")==0){
    ROLL_KP= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("ROLL_KP ")+std::string("set to ")+std::to_string(ROLL_KP)+';',1));
  }
  if(vect[0].compare("ROLL_TI")==0){
    ROLL_TI= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("ROLL_TI ")+std::string("set to ")+std::to_string(ROLL_TI)+';',1));
  }
  if(vect[0].compare("ROLL_TD")==0){
    ROLL_TD= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("ROLL_TD ")+std::string("set to ")+std::to_string(ROLL_TD)+';',1));
  }
  if(vect[0].compare("YAW_KP")==0){
    YAW_KP= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("YAW_KP ")+std::string("set to ")+std::to_string(YAW_KP)+';',1));
  }
   if(vect[0].compare("YAW_TI")==0){
    YAW_TI= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("YAW_TI ")+std::string("set to ")+std::to_string(YAW_TI)+';',1));
  }
   if(vect[0].compare("YAW_TD")==0){
    YAW_TD= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("YAW_TD ")+std::string("set to ")+std::to_string(YAW_TD)+';',1));
  }
  if(vect[0].compare("K_ARW")==0){
    K_ARW= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("K_ARW ")+std::string("set to ")+std::to_string(K_ARW)+';',1));
  }
  if(vect[0].compare("N_FILTER")==0){
    N_FILTER= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("N_FILTER ")+std::string("set to ")+std::to_string(N_FILTER)+';',1));
  }
  if(vect[0].compare("thrust_factor")==0){
    thrust_factor= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("thrust_factor ")+std::string("set to ")+std::to_string(thrust_factor)+';',1));
  }
  if(vect[0].compare("drag_factor")==0){
    drag_factor= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("drag_factor ")+std::string("set to ")+std::to_string(drag_factor)+';',1));
  }
  if(vect[0].compare("center_to_motor_distance")==0){
    center_to_motor_distance= std::atof(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("center_to_motor_distance ")+std::string("set to ")+std::to_string(center_to_motor_distance)+';',1));
  }
  if(vect[0].compare("MAX_MOTOR_SPEED")==0){
    MAX_MOTOR_SPEED= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MAX_MOTOR_SPEED ")+std::string("set to ")+std::to_string(MAX_MOTOR_SPEED)+';',1));
  }
  if(vect[0].compare("MAX_MOTOR_ACCELERATION")==0){
    MAX_MOTOR_ACCELERATION= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("MAX_MOTOR_ACCELERATION ")+std::string("set to ")+std::to_string(MAX_MOTOR_ACCELERATION)+';',1));
  }
  if(vect[0].compare("SERVO_MAX_REAL")==0){
    SERVO_MAX_REAL= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("SERVO_MAX_REAL ")+std::string("set to ")+std::to_string(SERVO_MAX_REAL)+';',1));
  }
  if(vect[0].compare("SERVO_VAL_MIN")==0){
    SERVO_VAL_MIN= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("SERVO_VAL_MIN ")+std::string("set to ")+std::to_string(SERVO_VAL_MIN)+';',1));
  }
   if(vect[0].compare("SERVO_VAL_MAX")==0){
    SERVO_VAL_MAX= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("SERVO_VAL_MAX ")+std::string("set to ")+std::to_string(SERVO_VAL_MAX)+';',1));
  }
  if(vect[0].compare("SERVO_INIT_PULSE")==0){
    SERVO_INIT_PULSE= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("SERVO_INIT_PULSE ")+std::string("set to ")+std::to_string(SERVO_INIT_PULSE)+';',1));
  }
  if(vect[0].compare("motorsTimeRate")==0){
    motorsTimeRate= std::atoi(vect[1].c_str());
    drone->sendMsg(new Message(Message::SYSTEM, std::string("CONFIG :")+std::string("motorsTimeRate ")+std::string("set to ")+std::to_string(motorsTimeRate)+';',1));
  }
  if(vect[0].compare("mCheckerThread")==0){
    mCheckerThread= std::atoi(vect[1].c_str());
  }
  if(vect[0].compare("xbeeListenerThread")==0){
    xbeeListenerThread= std::atoi(vect[1].c_str());
  }
  if(vect[0].compare("mProcessorThread")==0){
    mProcessorThread= std::atoi(vect[1].c_str());
  }
  if(vect[0].compare("mSenderThread")==0){
    mSenderThread= std::atoi(vect[1].c_str());
  }
  if(vect[0].compare("pingProcessorThread")==0){
    pingProcessorThread= std::atoi(vect[1].c_str());
  }
  if(vect[0].compare("eKFThread")==0){
    eKFThread= std::atoi(vect[1].c_str());
  }
  if(vect[0].compare("autoPilotThread")==0){
    autoPilotThread= std::atoi(vect[1].c_str());
  }
  if(vect[0].compare("eKFReaderThread")==0){
    eKFReaderThread= std::atoi(vect[1].c_str());
  }
  if(vect[0].compare("motorsThread")==0){
    motorsThread= std::atoi(vect[1].c_str());
  }
  

}


void Config::decompose(std::string* msg, std::string delimiter, std::vector<std::string> * vect){
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

int Config::write_config(){
  std::ofstream file(config_file, std::ios::trunc);
  file<<"Radioport;"<<Radio<<";\n";
  file<<"IMUport;"<<IMUport<<";\n";
  file<<"pingRate;"<<pingRate<<";\n";
  file<<"lostBeforeEmergency;"<<lostBeforeEmergency<<";\n";
  file<<"eKFTimeRate;"<<(int)eKFTimeRate<<";\n";
  file<<"autoPilotTimeRate;"<<(int)autoPilotTimeRate<<";\n";
  
  file<<"MAX_ALTI_TARGET;"<<MAX_ALTI_TARGET<<";\n";
  file<<"INI_ALTI_TARGET;"<<INI_ALTI_TARGET<<";\n";
  file<<"MAX_PITCH_TARGET;"<<MAX_PITCH_TARGET<<";\n";
  file<<"MAX_PITCH_TARGET;"<<MAX_PITCH_TARGET<<";\n";
  file<<"MAX_ROLL_TARGET;"<<MAX_ROLL_TARGET<<";\n";
  file<<"MAX_YAW_TARGET;"<<MAX_YAW_TARGET<<";\n";
  file<<"MIN_TIME_RATE;"<<MIN_TIME_RATE<<";\n";
  file<<"INTERP_TIME;"<<INTERP_TIME<<";\n";
  file<<"EXTREMUM_INTEGRAL_ERROR;"<<EXTREMUM_INTEGRAL_ERROR<<";\n";
  file<<"MAX_COMMAND_ALTI;"<<MAX_COMMAND_ALTI<<";\n";
  file<<"MIN_COMMAND_ALTI;"<<MIN_COMMAND_ALTI<<";\n";
  file<<"MAX_COMMAND_PITCH;"<<MAX_COMMAND_PITCH<<";\n";
  file<<"MIN_COMMAND_PITCH;"<<MIN_COMMAND_PITCH<<";\n";
  file<<"MAX_COMMAND_ROLL;"<<MAX_COMMAND_ROLL<<";\n";
  file<<"MIN_COMMAND_ROLL;"<<MIN_COMMAND_ROLL<<";\n";
  file<<"MAX_COMMAND_YAW;"<<MAX_COMMAND_YAW<<";\n";
  file<<"MIN_COMMAND_YAW;"<<MIN_COMMAND_YAW<<";\n";
  file<<"ALTI_KP;"<<ALTI_KP<<";\n";
  file<<"ALTI_TI;"<<ALTI_TI<<";\n";
  file<<"ALTI_TD;"<<ALTI_TD<<";\n";
  file<<"PITCH_KP;"<<PITCH_KP<<";\n";
  file<<"PITCH_TI;"<<PITCH_TI<<";\n";
  file<<"PITCH_TD;"<<PITCH_TD<<";\n";
  file<<"ROLL_KP;"<<ROLL_KP<<";\n";
  file<<"YAW_KP;"<<YAW_KP<<";\n";
  file<<"YAW_TI;"<<YAW_TI<<";\n";
  file<<"YAW_TD;"<<YAW_TD<<";\n";
  file<<"K_ARW;"<<K_ARW<<";\n";
  file<<"N_FILTER;"<<N_FILTER<<";\n";
  file<<"thrust_factor;"<<thrust_factor<<";\n";
  file<<"drag_factor;"<<drag_factor<<";\n";
  file<<"center_to_motor_distance;"<<center_to_motor_distance<<";\n";
  
  file<<"motorsTimeRate;"<<(int)motorsTimeRate<<";\n";
  file<<"mCheckerThread;"<<mCheckerThread<<";\n";
  file<<"xbeeListenerThread;"<<xbeeListenerThread<<";\n";
  file<<"mProcessorThread;"<<mProcessorThread<<";\n";
  file<<"mSenderThread;"<<mSenderThread<<";\n";
  file<<"pingProcessorThread;"<<pingProcessorThread<<";\n";
  file<<"eKFThread;"<<eKFThread<<";\n";
  file<<"autoPilotThread;"<<autoPilotThread<<";\n";
  file<<"eKFReaderThread;"<<eKFReaderThread<<";\n";
  file<<"motorsThread;"<<motorsThread<<";\n";
  
  file.close();
  
  
  
}
