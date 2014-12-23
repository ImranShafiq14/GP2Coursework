#include "Mouse.h"
#include <iostream>

//Constructor for Mouse - RT
Mouse::Mouse()
{
	absoluteMouseX = 0;
	absoluteMouseY = 0;
	relativeMouseX = 0;
	relativeMouseY = 0;
	mouseScroll = 0;
}

//Deconstructor for Mouse - RT
Mouse::~Mouse()
{

}

//Called by program every "frame" - RT
void Mouse::update()
{
	absoluteMouseX = 0;
	absoluteMouseY = 0;
	relativeMouseX = 0;
	relativeMouseY = 0;
	mouseScroll = 0;
}

//Called when user moves mouse, sets the absolute and relative positions of
//where the mouse is on-screen - RT
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

//Called when user moves the scroll wheel, tells the program if the wheel
//was scrolled up or down - RT
void Mouse::setMouseScroll(int mScroll)
{
	mouseScroll = mScroll;
}