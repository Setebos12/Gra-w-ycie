// Filename: fileIO.h
//
// Template methods for reading and writing game state to file
//
// Author: Piotr Pyrak

#pragma once

#include "fstream"

class FileIO {
public:
  static void init(const std::string &readFilePath,
                   const std::string &writeFilePath);

  const auto &getReadFile() { return readFilePath_; }
  const auto &getWriteFile() { return writeFilePath_; }

  FileIO() = default;

  template <typename T> bool read(T &obj) {
    if (!openStream(readFile_, readFilePath_))
      return false;
    readFile_ >> obj;
    if (readFile_.fail())
      return false;
    return true;
  }
  template <typename T> bool write(const T &obj) {
    if (!openStream(writeFile_, writeFilePath_))
      return false;
    writeFile_ << obj;
    if (writeFile_.fail())
      return false;
    return true;
  }

private:
  bool openStream(std::fstream &stream, const std::string &path);

  static std::string readFilePath_;
  static std::string writeFilePath_;
  std::fstream readFile_;
  std::fstream writeFile_;
};
