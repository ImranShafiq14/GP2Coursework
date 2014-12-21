#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "Component.h"

class Camera;

class CameraController :public Component
{
public:
	CameraController();
	~CameraController();

	void update();

	void setCamera(Camera * cam);
	void setCamSpeed(float speed);
private:
	float forwardSpeed;
	float strafeSpeed;
	float lookSpeed;
	Camera * attachedCamera;
};

#endif