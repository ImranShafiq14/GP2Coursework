#include "Input.h"

Input::Input()
{
	mouse = NULL;
	keyboard = NULL;
}

Input::~Input()
{

}

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

void Input::update()
{
	keyboard->update();
	mouse->update();
}

bool Input::init()
{
	keyboard = new Keyboard();
	mouse = new Mouse();

	return true;
}