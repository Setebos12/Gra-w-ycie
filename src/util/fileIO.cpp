// Filename: fileIO.cpp
//
// Implementation of static and nontemplate
//
// Author: Piotr Pyrak

#include "fileIO.h"

void FileIO::init(const std::string &readFilePath,
                  const std::string &writeFilePath) {
  readFilePath_ = readFilePath;
  writeFilePath_ = writeFilePath;

  std::fstream readCheck{readFilePath_};
  if (readFilePath_ != "" && !readCheck.is_open()) {
    throw std::runtime_error("Failed to open file: " + readFilePath_);
  }
  std::fstream writeCheck{writeFilePath_};
  if (writeFilePath_ != "" && !writeCheck.is_open()) {
    throw std::runtime_error("Failed to open file: " + writeFilePath_);
  }
}

bool FileIO::openStream(std::fstream &stream, const std::string &path) {
  if (path != "" && !stream.is_open()) {
    std::fstream stream{path};

    if (!stream.is_open())
      return false;
  }
  return true;
}

std::string FileIO::readFilePath_;
std::string FileIO::writeFilePath_;
