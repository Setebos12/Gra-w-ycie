// Gra w zycie.cpp : Defines the entry point for the application.
//
// Author: Piotr Pyrak

#include "core/Simulation.h"
#include "util/parser.h"
#include "util/logger.h"
#include "util/fileIO.h"

using namespace std;

int main(int argc, char *argv[])
{
	Parser parser(argc, argv);

	Util::Level lvl {Util::Level::DEBUG};
	auto optlvl {parser.getArg<Util::Level>("--level")};
	if (optlvl.has_value()) {
		lvl = *optlvl;
	}

	auto optReadPath = parser.getArg<std::string>("--read");
	auto optWritePath = parser.getArg<std::string>("--write");

	auto readPath = optReadPath.has_value() ? optReadPath.value() : "";
	auto writePath = optWritePath.has_value() ? optWritePath.value() : "";

	FileIO::init(readPath, writePath);

	std::shared_ptr<MVC::Simulation> sim = std::make_shared<MVC::Simulation>(lvl);

	sim->initWindow(std::weak_ptr(sim));

	sim->run();

	return 0;
}
