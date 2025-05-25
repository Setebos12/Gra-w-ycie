// Fielname: logger.cpp
//
// A class that prints out messages (used with events)
//
// Author: Krzysztof Rutkowski (init), Piotr Pyrak

#pragma once

#include <string>

namespace Util {
enum class Level { ERROR, INFO, DEBUG };

class Logger {
public:
  Logger(Level level) : loggerLevel_(level) {}

  void setLoggerLevel(Level newLevel) { loggerLevel_ = newLevel; }
  Level getLoggerLevel() const { return loggerLevel_; }

  void log(const std::string &message, Level level) const;

private:
  Level loggerLevel_;
};
} // namespace Util
