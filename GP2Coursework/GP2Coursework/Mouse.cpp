#include "Mouse.h"
#include <iostream>

Mouse::Mouse()
{
	absoluteMouseX = 0;
	absoluteMouseY = 0;
	relativeMouseX = 0;
	relativeMouseY = 0;
	mouseScroll = 0;
}

Mouse::~Mouse()
{

}

void Mouse::update()
{
	absoluteMouseX = 0;
	absoluteMouseY = 0;
	relativeMouseX = 0;
	relativeMouseY = 0;
	mouseScroll = 0;
}

void Mouse::setMousePosition(int absoluteX, int absoluteY, int relativeX, int relativeY)
{
	absoluteMouseX = absoluteX;
	absoluteMouseY = absoluteY;
	if (relativeX > 100)
		relativeMouseX = 100;
	else
		relativeMouseX = relativeX;
	if (relativeY > 100)
		relativeMouseY = 100;
	else
		relativeMouseY = relativeY;
	/*relativeMouseX = relativeX;
	relativeMouseY = relativeY;*/

	 std::cout << "Relative mouse positions " << relativeMouseX << " " << relativeMouseY << std::endl;
}

void Mouse::setMouseScroll(int mScroll)
{
	mouseScroll = mScroll;
}