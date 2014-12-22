#ifndef POST_PROCESSING_H
#define POST_PROCESSING_H

using namespace std;

#include <GL/glew.h>
#include <string>
#include <SDL_opengl.h>
#include <GL/GLU.h>

class PostProcessing
{
public:
	PostProcessing();
	~PostProcessing();

	void init(int width, int height, string& vertexShaderFilename, string& fragmentShaderFilename);

	void bind();

	void preDraw();
	void draw();
	void postDraw();

	void destroy();

	GLint getUniformVariableLocation(const string& name);
private:
	void createShader(string& vertexShaderFilename, string& fragmentShaderFilename);
	void createFullScreenQuad();
	void createFramebuffer(int width, int height);

	GLuint frameBufferObject;
	GLuint depthBufferObject;
	GLuint FBOTexture;

	GLuint fullScreenVBO;

	GLuint postProcessingProgram;

	int width;
	int height;
};

#endif