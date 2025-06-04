// Fielname: logger.cpp
//
// Implementation of logger class
//
// Author: Piotr Pyrak

#include "logger.h"
#include <iostream>

using namespace Util;

void Logger::log(const std::string &message, Level level) const {
  if (level <= loggerLevel_) {
    if (level == Level::ERROR)
      std::cerr << message << std::endl;
    else
      std::cout << message << std::endl;
  }
}
