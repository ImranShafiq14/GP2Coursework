#include "Input.h"

//Constructor for Input - RT
Input::Input()
{
	mouse = NULL;
	keyboard = NULL;
}

//Deconstructor for Input - RT
Input::~Input()
{

}

//Called when program is closing - RT
void Input::destroy()
{
	if (mouse)
	{
		delete mouse;
		mouse = NULL;
	}
	if (keyboard)
	{
		delete keyboard;
		keyboard = NULL;
	}
}

//Called by program every "frame" - RT
void Input::update()
{
	keyboard->update();
	mouse->update();
}

//Called when input is being initialised - RT
bool Input::init()
{
	keyboard = new Keyboard();
	mouse = new Mouse();

	return true;
}