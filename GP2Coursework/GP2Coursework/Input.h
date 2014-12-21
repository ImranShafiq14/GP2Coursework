#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

#include <string>
#include <vector>

#include <SDL.h>

#include "Keyboard.h"
#include "Mouse.h"

using namespace std;

class Input
{
public:
	Input();
	~Input();

	bool init();
	void destroy();
	void update();

	Keyboard * getKeyboard()
	{
		return keyboard;
	};

	Mouse * getMouse()
	{
		return mouse;
	};

	static Input& getInput()
	{
		static Input input;
		return input;
	}

private:
	Keyboard * keyboard;
	Mouse * mouse;
protected:
};

#endif