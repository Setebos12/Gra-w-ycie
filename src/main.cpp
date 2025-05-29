// Gra w zycie.cpp : Defines the entry point for the application.
//
// Author: Piotr Pyrak

#include "core/Simulation.h"
#include "util/parser.h"
#include "util/logger.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	Parser parser(argc, argv);

	Util::Level lvl {Util::Level::DEBUG};
	auto optlvl {parser.getArg<Util::Level>("--level")};
	if (optlvl.has_value()) {
		lvl = *optlvl;
	}

	parser.getArg<std::string>("--read");
	parser.getArg<std::string>("--write");
	
	//MVC::Simulation sim;

	//sim.run();

	return 0;
}
