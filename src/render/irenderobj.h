//Filename: irenderobj.h
//
//An interface that an object interacting with the render needs to implement
//
//Author: Piotr Pyrak

#pragma once

#include "drawer.h"

namespace Render {
class IRenderObject {
public:
	virtual ~IRenderObject() = default;
	virtual void draw(Drawer& draw) = 0;
};
}
