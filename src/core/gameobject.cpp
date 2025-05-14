// Filename: gameobject.cpp
//
// Implementation for friend operators
//
// Author: Piotr Pyrak

#include "gameobject.h"

using namespace MVC;

std::ostream &operator<<(std::ostream &write, const GameObject &gameObj) {
	write << gameObj.printString();

	return write;
}

std::istream &operator>>(std::istream &read, GameObject &gameObj) {
	if (read.fail())
		return read;
	
	std::string readString;

	read >> readString;

	if (read.fail())
		return read;

	gameObj.readString(readString);

	return read;
}
