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

CameraController::CameraController()
{
	attachedCamera = NULL;
	forwardSpeed = 4;
	strafeSpeed = 4;
	lookSpeed = 0.1f;
	m_Type = "Camera Controller";
}

CameraController::~CameraController()
{

}

void CameraController::update()
{
	if (attachedCamera)
	{
		vec3 currentPosition = attachedCamera->getParent()->getTransform()->getPosition();
		vec3 currentRotation = attachedCamera->getParent()->getTransform()->getRotation();
		vec3 currentLook = attachedCamera->getLookAt();

		int mouseX = Input::getInput().getMouse()->getRelativeMouseX();
		int mouseY = Input::getInput().getMouse()->getRelativeMouseY();

		currentRotation.x += mouseX * Timer::getTimer().getDeltaTime() * lookSpeed;
		currentRotation.y += mouseY * Timer::getTimer().getDeltaTime() * lookSpeed;

		vec3 direction(cos(currentRotation.y) * sin(currentRotation.x),
			sin(currentRotation.y),
			cos(currentRotation.y) * cos(currentRotation.x));

		vec3 right = vec3(sin(currentRotation.x - 3.14f / 2.0f), 0, cos(currentRotation.y - 3.14 / 2.0f));

		glm::vec3 up = glm::cross(direction, right);

		/*cout << "Mouse " << mouseX << " " << mouseY << endl;
		cout << "Direction " << direction.x << " " << direction.y << endl;*/

		/*cout << "Camera Position " << (float)attachedCamera->getParent()->getTransform()->getPosition().x << " " <<
			(float)attachedCamera->getParent()->getTransform()->getPosition().y << " " << 
			(float)attachedCamera->getParent()->getTransform()->getPosition().z << endl;*/

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

		attachedCamera->getParent()->getTransform()->setPosition(currentPosition.x, currentPosition.y, currentPosition.z);
		attachedCamera->getParent()->getTransform()->setRotation(currentRotation.x, currentRotation.y, currentRotation.z);
		attachedCamera->setUp(up.x, up.y, up.z);
		attachedCamera->setLookAt(currentPosition.x + direction.x, currentPosition.y + direction.y, currentPosition.z + direction.z);

	}
}

void CameraController::setCamera(Camera * cam)
{
	attachedCamera = cam;
}