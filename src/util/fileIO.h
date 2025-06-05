// Filename: fileIO.h
//
// Template methods for reading and writing game state to file
//
// Author: Piotr Pyrak

#pragma once

#include "fstream"

namespace Util {
class FileIO {
public:
    static void init(const std::string& readFilePath,
                     const std::string& writeFilePath);

    const auto& getReadFile() { return readFilePath_; }
    const auto& getWriteFile() { return writeFilePath_; }

    FileIO() = default;
    ~FileIO() {
        readFile_.close();
        writeFile_.close();
    }

    //copy
    FileIO(const FileIO&) = delete;
    FileIO& operator=(const FileIO&) = delete;

    //move
    FileIO(FileIO&& other) noexcept
        : readFile_(std::move(other.readFile_)),
        writeFile_(std::move(other.writeFile_)) {
    }
    FileIO& operator=(FileIO&& other) noexcept {
        if (this != &other) {
            readFile_.close();
            writeFile_.close();
            readFile_ = std::move(other.readFile_);
            writeFile_ = std::move(other.writeFile_);
        }
        return *this;
    }

    template <typename T> void read(T& obj) {
        try {
            if (!openStream(readFile_, readFilePath_))
                throw std::runtime_error("Failed to open file: " + readFilePath_);
            readFile_ >> obj;
            if (readFile_.fail())
                throw std::runtime_error("Failed to read from file: " + readFilePath_);
        } catch (...) { throw; }
    }

    template <typename T> void write(const T& obj) {
        try {
            if (!openStream(writeFile_, writeFilePath_))
                throw std::runtime_error("Failed to open file: " + writeFilePath_);
            writeFile_ << obj;
            if (writeFile_.fail())
                throw std::runtime_error("Failed to write to file: " + writeFilePath_);
        } catch (...) { throw; }
    }

private:
    bool openStream(std::fstream& stream, const std::string& path);

    static std::string readFilePath_;
    static std::string writeFilePath_;
    std::fstream readFile_;
    std::fstream writeFile_;
};
}