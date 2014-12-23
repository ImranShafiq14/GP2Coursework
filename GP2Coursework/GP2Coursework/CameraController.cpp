#include <iostream>

#include "CameraController.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Timer.h"
#include "Input.h"

#include <glm/glm.hpp>
using glm::vec3;

using namespace std;

//Constructor for CameraController - RT
CameraController::CameraController()
{
	attachedCamera = NULL;
	forwardSpeed = 100;
	strafeSpeed = 100;
	lookSpeed = 0.1f;
	m_Type = "Camera Controller";
	debugMode = false;
}

//Deconstructor for CameraController - RT
CameraController::~CameraController()
{

}

//Called by program each "frame" - RT
void CameraController::update()
{
	if (attachedCamera)
	{
		//pulls values from camera - RT
		vec3 currentPosition = attachedCamera->getParent()->getTransform()->getPosition();
		vec3 currentRotation = attachedCamera->getParent()->getTransform()->getRotation();
		vec3 currentLook = attachedCamera->getLookAt();

		//pulls mouse values from mouse - rt
		int mouseX = Input::getInput().getMouse()->getRelativeMouseX();
		int mouseY = Input::getInput().getMouse()->getRelativeMouseY();

		//calculates new rotation based on mouse values, time elapsed and speed of look - RT
		currentRotation.x += mouseX * Timer::getTimer().getDeltaTime() * lookSpeed;
		currentRotation.y += mouseY * Timer::getTimer().getDeltaTime() * lookSpeed;

		//creates vector of where player is looking - RT
		vec3 direction(cos(currentRotation.y) * sin(currentRotation.x),
			sin(currentRotation.y),
			cos(currentRotation.y) * cos(currentRotation.x));

		vec3 right = vec3(sin(currentRotation.x - 3.14f / 2.0f), 0, cos(currentRotation.y - 3.14 / 2.0f));

		glm::vec3 up = glm::cross(direction, right);

		//polls keyboard input from user and moves camera as appropriate
		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_w))
		{
			currentPosition.z += direction.z * forwardSpeed * Timer::getTimer().getDeltaTime();
			//currentLook.z += direction.z*forwardSpeed*Timer::getTimer().getDeltaTime();
		}
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_s))
		{
			currentPosition.z -= direction.z * forwardSpeed * Timer::getTimer().getDeltaTime();
			//currentLook.z -= direction.z*forwardSpeed*Timer::getTimer().getDeltaTime();
		}
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_a))
		{
			currentPosition += right * strafeSpeed * Timer::getTimer().getDeltaTime();
			//currentLook += right*strafeSpeed*Timer::getTimer().getDeltaTime();
		}
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_d))
		{
			currentPosition -= right * strafeSpeed * Timer::getTimer().getDeltaTime();
			//currentLook += right*(strafeSpeed*-1)*Timer::getTimer().getDeltaTime();
		}
		//toggles debug mode based on user input - RT
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_p))
		{
			debugMode = !debugMode;
		}
		//moves y axis if user in debug mode based on mouse scroll - RT
		else if (Input::getInput().getMouse()->getMouseScroll() != 0)
		{
			if (debugMode)
			{
				if (Input::getInput().getMouse()->getMouseScroll() == 1)
				{
					currentPosition.y += direction.y * forwardSpeed * Timer::getTimer().getDeltaTime();
				}
				else if (Input::getInput().getMouse()->getMouseScroll() == -1)
				{
					currentPosition.y -= direction.y * forwardSpeed * Timer::getTimer().getDeltaTime();
				}
			}
		}
		
		//Moves player back to correct y position when moving from debug to player cameras - RT
		if (!debugMode)
		{
			currentPosition.y = 2.0f;
		}

		//updates camera values- RT
		attachedCamera->getParent()->getTransform()->setPosition(currentPosition.x, currentPosition.y, currentPosition.z);
		attachedCamera->getParent()->getTransform()->setRotation(currentRotation.x, currentRotation.y, currentRotation.z);
		attachedCamera->setUp(up.x, up.y, up.z);
		attachedCamera->setLookAt(currentPosition.x + direction.x, currentPosition.y + direction.y, currentPosition.z + direction.z);

	}
}

//Sets the Camera to be manipulated - RT
void CameraController::setCamera(Camera * cam)
{
	attachedCamera = cam;
}

//Toggles debug mode - RT
void CameraController::toggleDebugMode()
{
	debugMode = !debugMode;
}

//returns the debug mode state - RT
bool CameraController::getDebugMode()
{
	return debugMode;
}