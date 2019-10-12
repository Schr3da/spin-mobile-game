#ifndef LOGGER_HH
#define LOGGER_HH

#include <string>
#include "Settings.h"
#include <iostream>
#include <stdexcept>

class Logger{
 public:
  enum LogLevel{
    DEBUG_LOW,
    DEBUG,
    ERROR
  };

  static const LogLevel LOG_LEVEL = ERROR;

  static void log(string message, LogLevel log_level=DEBUG){
    if (ignoreLogLevel(log_level)){
      return;
    }
    if (log_level==DEBUG){
      cout<<"DEBUG: "<<message<<endl;
    }
    else  if (log_level==ERROR){
      cout<<"ERROR: "<<message<<endl;
    }
    else  if (log_level==DEBUG_LOW){
      cout<<"DEBUG_LOW: "<<message<<endl;
    }
    else {
      throw invalid_argument("Logger::log() called with an invalid loglevel");
    }
  }

  static  bool ignoreLogLevel(LogLevel level){
    if (LOG_LEVEL == DEBUG_LOW){
      return false;
    }
    if (LOG_LEVEL == DEBUG){
      return level==DEBUG_LOW;
    }
    if (LOG_LEVEL == ERROR){
      return level!=ERROR;
    }
  }
};

#endif
