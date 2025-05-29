// Fielname: logger.cpp
//
// A class that prints out messages (used with events)
//
// Author: Krzysztof Rutkowski (init), Piotr Pyrak

#pragma once

#include <istream>
#include <string>

namespace Util {
enum class Level { ERROR, INFO, DEBUG };

static std::istream &operator>>(std::istream &read, Level &lvl) {
  if (read.fail())
    return read;

  std::string token;
  read >> token;

  if (token == "error")
    lvl = Level::ERROR;
  else if (token == "info")
    lvl = Level::INFO;
  else if (token == "debug")
    lvl = Level::DEBUG;
  else
    lvl = Level::ERROR;

  return read;
}

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
