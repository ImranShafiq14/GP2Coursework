#include "SkyboxMaterial.h"
#include "Texture.h"
#include "Vertex.h"

//Constructor for SkyBoxMaterial - RT
SkyBoxMaterial::SkyBoxMaterial()
{
	m_CubeTexture = 0;
}

//Deconstructor for SkyBoxMaterial - RT
SkyBoxMaterial::~SkyBoxMaterial()
{

}

//Called when program is closing - RT
void SkyBoxMaterial::destroy()
{
	if (m_CubeTexture)
	{
		glDeleteTextures(1, &m_CubeTexture);
	}
}

//Binds the textures of the SkyBox - RT
void SkyBoxMaterial::bind()
{
	glDepthMask(GL_FALSE);
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeTexture);

	GLint vertexPosLocation = glGetAttribLocation(m_ShaderProgram, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, vertexPosLocation, "vertexPosition");

	glEnableVertexAttribArray(vertexPosLocation);
	glVertexAttribPointer(vertexPosLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
}

//Unbinds textures - RT
void SkyBoxMaterial::unbind()
{
	glDepthMask(GL_TRUE);
}

//Loads cube textures with the 6 sides of the cube passed in as parameters - RT
void SkyBoxMaterial::loadCubeTexture(const string& filenamePosZ, const string& filenameNegZ, const string& filenamePosX,
	const string& filenameNegX, const string& filenamePosY, const string& filenameNegY)
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_CubeTexture);

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);

	loadCubeMapSide(filenamePosZ, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	loadCubeMapSide(filenameNegZ, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	loadCubeMapSide(filenamePosX, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	loadCubeMapSide(filenameNegX, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	loadCubeMapSide(filenamePosY, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	loadCubeMapSide(filenameNegY, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);

}

//Returns the cube texture - RT
GLuint SkyBoxMaterial::getCubeTexture()
{
	return m_CubeTexture;
}