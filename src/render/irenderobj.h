//Filename: irenderobj.h
//
//An interface that an object interacting with the render needs to implement
//
//Author: Piotr Pyrak

#include "drawer.h"

namespace Render {
class IRenderObject {
	virtual void draw(const Drawer& draw) = 0;
};
}
