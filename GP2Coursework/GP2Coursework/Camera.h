#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"

//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera : public Component
{
public:
	Camera();
	~Camera();

	void setLookAt(float x, float y, float z);
	void setUp(float x, float y, float z);
	void setFOV(float FOV);
	void setAspectRatio(float aspectRatio);
	void setNearClip(float nearClip);
	void setFarClip(float farClip);

	vec3 getLookAt();

	mat4 getViewMatrix();
	mat4 getProjectMatrix();
	void update();
private:
	vec3 m_LookAt;
	vec3 m_Up;
	float m_FOV;
	float m_AspectRatio;
	float m_NearClip;
	float m_FarClip;
	mat4 m_ViewMatrix;
	mat4 m_ProjectionMatrix;
};

#endif