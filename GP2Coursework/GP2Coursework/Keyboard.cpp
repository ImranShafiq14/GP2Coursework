#include "Keyboard.h"

//Constructor for Keyboard - RT
Keyboard::Keyboard()
{
	for (int i = 0; i < MAX_NO_KEYS; i++)
	{
		keysDown[i] = false;
		keysUp[i] = false;
	}
}

//Deconstructor for Keyboard - RT
Keyboard::~Keyboard()
{

}

//called by program each "frame" - RT
void Keyboard::update()
{
	for (int i = 0; i < MAX_NO_KEYS; i++)
	{
		keysDown[i] = false;
		keysUp[i] = false;
	}
}

//sets key(s) down to be which ever key(s) the user is pressing - RT
void Keyboard::setKeyDown(short index)
{

	keysDown[index] = true;

}
//sets key(s) up to be whatever key(s) the user isn't pressing - RT
void Keyboard::setKeyUp(short index)
{
	keysUp[index] = true;
}

//finds out if a specific key is being pressed by user - RT
bool Keyboard::isKeyDown(short index)
{
	return keysDown[index];
}

//finds out if user isn't pressing a specific key - RT
bool Keyboard::isKeyUp(short index)
{
	return keysUp[index];
}