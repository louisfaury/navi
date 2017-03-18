//
//  INS_Exception.cpp
//  Navi_Exception
//
//  Created by Louis Faury on 29/12/2015.
//  Copyright © 2015 Louis Faury. All rights reserved.
//

#include "../Navi_Exception/INS_Exception.hpp"


INS_Exception::INS_Exception(){
}

INS_Exception::INS_Exception(ERROR_TYPE error_type,std::string msg) : _msg(msg), _error_type(error_type){
}

INS_Exception::INS_Exception(ERROR_TYPE error_type,std::string captor_id,std::string msg) : _msg(msg), _error_type(error_type), _captor_id(captor_id){
}


const char * INS_Exception::what() const throw() {

    std::string foo = "Inertial Navigation System Exception --> ";
    switch (_error_type) {

        case reading : {
            foo += "Reading Error : ";
            break;
        }
        case calib : {
            foo += "Calibration Error : ";
            break;
        }
        case init : {
            foo += "Initialisation Error : ";
        }
        default : {
            foo += "System Error : ";
        }
    }

    foo += _msg;
    foo += '(';
    foo += _captor_id;
    foo+= ')';
    foo += '\n';
    const char * result = foo.c_str();
    return result;
}


INS_Exception::~INS_Exception() {
}
