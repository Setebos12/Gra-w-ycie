//Filename: gameobject.h
//
//All objects that need to interact with the game loop will inherit this class,
//requires implementation of draw and update functions.
//
//Author: Piotr Pyrak

#pragma once

#include <string>
#include "drawer.h"

class GameObject {
public:
	GameObject(const std::string& name) : name_(name) {}

	//recivers renderer object where it will be able to call drawing methods
	virtual void draw(const Drawer& drawer) = 0;
	virtual void update() = 0;

	const auto& getName() {return name_;}
	void setName(const std::string& name) {name_=name;}
private:
	std::string name_;
};
