#ifndef SHADOW_MAPPING_H
#define SHADOW_MAPPING_H

#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>

#include "Timer.h"
#include "Camera.h"
#include "Light.h"
#include "Transform.h"

#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;
using glm::vec4;

using namespace std;

class ShadowMapping
{
public:
	bool init();
	void display();
private:
	vec3 cameraPosition;
	vec3 lightPosition;

	GLuint shadowMapTexture;

	mat4 lightProjectionMatrix;
	mat4 lightViewMatrix;
	mat4 cameraProjectionMatrix;
	mat4 cameraViewMatrix;
protected:
	const int shadowMapSize = 512;
	const int windowWidth = 1280;
	const int windowHeight = 720;
};

#endif