// Filename: fileIO.cpp
//
// Implementation of static and nontemplate
//
// Author: Piotr Pyrak

#include "fileIO.h"

using namespace Util;

void FileIO::init(const std::string &readFilePath,
                  const std::string &writeFilePath) {
    try {
        readFilePath_ = readFilePath;
        writeFilePath_ = writeFilePath;

        std::fstream readCheck{ readFilePath_ };
        if (readFilePath_ != "" && !readCheck.is_open()) {
            throw std::runtime_error("Failed to open file: " + readFilePath_);
        }
        std::fstream writeCheck{ writeFilePath_, std::fstream::out };
        if (writeFilePath_ != "" && !writeCheck.is_open()) {
            throw std::runtime_error("Failed to open file: " + writeFilePath_);
        }
    } catch (...) { throw; }
}

bool FileIO::openStream(std::fstream &stream, const std::string &path) {
  if (path != "" && !stream.is_open()) {
    stream = std::fstream{path};

    if (!stream.is_open() || stream.fail())
      return false;
  }
  return true;
}

std::string FileIO::readFilePath_;
std::string FileIO::writeFilePath_;
