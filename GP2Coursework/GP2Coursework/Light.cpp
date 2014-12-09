#include "Light.h"

Light::Light()
{
	m_Type = "Light";
	m_DiffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_LightDirection = vec3(0.5f, 0.5f, 0.5f);
	m_SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

Light::~Light()
{

}

vec4& Light::getDiffuseColour()
{
	return m_DiffuseColour;
}

void Light::setDiffuseColour(float r, float g, float b, float a)
{
	m_DiffuseColour = vec4(r, g, b, a);
}

vec3& Light::getLightDirection()
{
	return m_LightDirection;
}

void Light::setLightDirection(float x, float y, float z)
{
	m_LightDirection = vec3(x, y, z);
}

vec4& Light::getSpecularColour()
{
	return m_SpecularColour;
}

void Light::setSpecularColour(float r, float g, float b, float a)
{
	m_SpecularColour = vec4(r, g, b, a);
}