#include "PostProcessing.h"
#include "Shader.h"

PostProcessing::PostProcessing()
{
	frameBufferObject = 0;
	depthBufferObject = 0;
	FBOTexture = 0;
	fullScreenVBO = 0;
	postProcessingProgram = 0;
}

PostProcessing::~PostProcessing()
{

}

void PostProcessing::init(int width, int height, string& vertexShaderFilename, string& fragmentShaderFilename)
{
	createFramebuffer(width, height);
	createShader(vertexShaderFilename, fragmentShaderFilename);
	createFullScreenQuad();

}

void PostProcessing::createShader(string& vertexShaderFilename, string& fragmentShaderFilename)
{
	GLuint vertexShaderProgram = 0;
	vertexShaderProgram = loadShaderFromFile(vertexShaderFilename, VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
	fragmentShaderProgram = loadShaderFromFile(fragmentShaderFilename, FRAGMENT_SHADER);

	postProcessingProgram = glCreateProgram();

	glAttachShader(postProcessingProgram, vertexShaderProgram);
	glAttachShader(postProcessingProgram, fragmentShaderProgram);
	glLinkProgram(postProcessingProgram);
	checkForLinkErrors(postProcessingProgram);

	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	glBindAttribLocation(postProcessingProgram, 0, "vertexPosition");

}

void PostProcessing::createFullScreenQuad()
{
	GLfloat vertices[]{
			-1, 1,
			1, -1,
			-1, 1,
			1, 1
	};

	glGenFramebuffers(1, &fullScreenVBO);
	glBindBuffer(GL_ARRAY_BUFFER, fullScreenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void PostProcessing::createFramebuffer(int width, int height)
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &FBOTexture);
	glBindTexture(GL_TEXTURE_2D, FBOTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenRenderbuffers(1, &depthBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenFramebuffers(1, &frameBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBOTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferObject);

	GLenum status;

	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "BUFFER IN POSTPROCESSING BROKEN SOMEHOW" << endl;
		//BAD THINGS HAVE HAPPENED
	}

}

void PostProcessing::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
}

void PostProcessing::preDraw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, FBOTexture);

	glUseProgram(postProcessingProgram);
	GLint textureLocation = glGetUniformLocation(postProcessingProgram, "texture0");
	glUniform1i(textureLocation, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, fullScreenVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void PostProcessing::postDraw()
{
	glDisableVertexAttribArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


}
void PostProcessing::draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void PostProcessing::destroy()
{
	glDeleteBuffers(1, &fullScreenVBO);
	glDeleteProgram(postProcessingProgram);
	glDeleteRenderbuffers(1, &depthBufferObject);
	glDeleteTextures(1, &FBOTexture);
	glDeleteFramebuffers(1, &frameBufferObject);

}
GLint PostProcessing::getUniformVariableLocation(const string& name)
{
	return glGetUniformLocation(postProcessingProgram, name.c_str());
}