#ifndef LIGHT_H
#define LIGHT_H

#include "Component.h"

#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;

class Light : public Component
{
public:
	Light();
	~Light();

	vec4& getDiffuseColour();
	void setDiffuseColour(float r, float g, float b, float a);
	
	vec3& getLightDirection();
	void setLightDirection(float x, float y, float z);

	vec4& getSpecularColour();
	void setSpecularColour(float r, float g, float b, float a);
private:
	vec4 m_DiffuseColour;
	vec3 m_LightDirection;
	vec4 m_SpecularColour;
};

#endif