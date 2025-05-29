// Filename: parser.h
//
// Class responsible for parsing input arguments
//
// Author: Piotr Pyrak

#pragma once

#include <optional>
#include <sstream>
#include <string>
#include <vector>

class Parser {
public:
  Parser(int argc, char *argv[]) : argc_(argc) {
    for (int i = 0; i < argc; ++i) {
      arguments_.push_back(std::string(argv[i]));
    }
  }

  bool getFlag(const std::string &flag) {
    for (const auto &arg : arguments_) {
      if (arg == flag)
        return true;
    }
    return false;
  }

  template <typename T> std::optional<T> getArg(const std::string &flag) {
    for (auto it = arguments_.begin(); it != arguments_.end(); ++it) {
      if (*it == flag) {
        if ((it + 1) != arguments_.end()) {
          std::stringstream ss(*(it + 1));
          T type;
          ss >> type;
          if (ss.fail())
            return std::nullopt;
          return type;
        }
      }
    }
    return std::nullopt;
  }

private:
  int argc_;
  std::vector<std::string> arguments_;
};
