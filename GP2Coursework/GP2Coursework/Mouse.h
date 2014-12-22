#ifndef MOUSE_H
#define MOUSE_H

class Mouse
{
public:
	Mouse();
	~Mouse();

	void update();

	void setMousePosition(int absoluteX, int absoluteY, int relativeX, int relativeY);

	int getRelativeMouseX()
	{
		return relativeMouseX;
	};

	int getRelativeMouseY()
	{
		return relativeMouseY;
	}

	void setMouseScroll(int mScroll);

	int getMouseScroll()
	{
		return mouseScroll;
	}
private:
	int absoluteMouseX;
	int absoluteMouseY;
	int relativeMouseX;
	int relativeMouseY;
	int mouseScroll;
};


#endif