//Filename: parser.h
//
//Class responsible for parsing input arguments
//
//Author: Piotr Pyrak

#pragma once

#include <vector>
#include <string>

class Parser {
public:
	Parser(int argc, char* argv[]) : argc_(argc) {
		for (int i = 0; i < argc; ++i) {
			arguments_.push_back(std::string(argv[i]));
		}
	}
private:
	int argc;
	std::vector<std::string> arguments_;
};