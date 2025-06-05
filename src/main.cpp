// Gra w zycie.cpp : Defines the entry point for the application.
//
// Author: Piotr Pyrak

#include "simulation.h"
#include "parser.h"
#include "logger.h"
#include "fileIO.h"

using namespace std;

int main(int argc, char *argv[])
{
	Util::Parser parser(argc, argv);

	Util::Level lvl {Util::Level::DEBUG};
	auto optlvl {parser.getArg<Util::Level>("--level")};
	if (optlvl.has_value()) {
		lvl = *optlvl;
	}

	auto optReadPath = parser.getArg<std::string>("--read");
	auto optWritePath = parser.getArg<std::string>("--write");

	auto readPath = optReadPath.has_value() ? optReadPath.value() : "";
	auto writePath = optWritePath.has_value() ? optWritePath.value() : "";

	try {
		Util::FileIO::init(readPath, writePath);
	} catch (runtime_error err) {
		std::cerr << "Failed read/write of FileIO:  " << err.what() << std::endl;
	}

	std::shared_ptr<MVC::Simulation> sim = std::make_shared<MVC::Simulation>(lvl);

	sim->initWindow(std::weak_ptr(sim));

	sim->run();

	return 0;
}
