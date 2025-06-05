// Filename: gameobject.cpp
//
// Implementation for friend operators
//
// Author: Piotr Pyrak

#include "gameobject.h"

namespace MVC {
std::ostream& operator<<(std::ostream& write, const GameObject& gameObj) {
	write << gameObj.printString();

	if (!write.fail())
		gameObj.logEvent_.value()->invoke("write stream gameobject success: " + gameObj.name_, Util::Level::INFO);

	return write;
}

std::istream& operator>>(std::istream& read, GameObject& gameObj) {
	if (read.fail())
		return read;

	std::string readString;

	std::getline(read, readString);

	if (read.fail())
		return read;

	gameObj.readString(readString);

	if (read.fail())
		return read;

	gameObj.logEvent_.value()->invoke("read stream gameobject success: " + gameObj.name_, Util::Level::INFO);

	return read;
}
} // namespace MVC
