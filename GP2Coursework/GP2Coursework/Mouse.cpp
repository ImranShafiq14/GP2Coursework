#include "Mouse.h"

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
	relativeMouseX = relativeX;
	relativeMouseY = relativeY;
}

void Mouse::setMouseScroll(int mScroll)
{
	mouseScroll = mScroll;
}