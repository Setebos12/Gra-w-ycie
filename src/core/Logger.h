#pragma once

#include <iostream>
#include <string>

class Logger {
public:
	static void error(const std::string& message, const std::ostream& os = std::cerr);
	static void info(const std::string& message,const std::ostream& os = std::cout);
	static void debug(const std::string& message,const std::ostream& os = std::cout);
};