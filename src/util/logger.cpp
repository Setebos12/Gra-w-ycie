// Fielname: logger.cpp
//
// Implementation of logger class
//
// Author: Piotr Pyrak

#include "logger.h"
#include <iostream>

using namespace Util;

void Logger::log(const std::string &message, Level level) {
  if (level >= loggerLevel_) {
    if (level == Level::ERROR)
      std::cerr << message;
    else
      std::cerr << message;
  }
}
