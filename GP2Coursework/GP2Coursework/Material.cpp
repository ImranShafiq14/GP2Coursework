#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"
#include "TextureManager.h"

bool BaseMaterial::loadShader(const std::string& vsFilename, const std::string& fsFilename)
{
	GLuint vertexShaderProgram = 0;
	vertexShaderProgram = loadShaderFromFile(const_cast<std::string&>(vsFilename), VERTEX_SHADER);
	
	GLuint fragmentShaderProgram = 0;
	fragmentShaderProgram = loadShaderFromFile(const_cast<std::string&>(fsFilename), FRAGMENT_SHADER);
	
	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);
	
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
	
	return true;
}

GLint BaseMaterial::getUniformLocation(const std::string& name)
{
	return glGetUniformLocation(m_ShaderProgram, name.c_str());
}

Material::Material()
{
	//m_Type = "Material";
	//m_ShaderProgram = -1;
	//m_AmbientColour = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	////m_DiffuseColour = vec4(0.75f, 0.75f, 0.75f, 1.0f);
	//m_DiffuseColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	////m_SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_SpecularColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	//m_SpecularPower = 200.0f;
	//m_DiffuseMap = 0;
	//m_SpecularMap = 0;

	//Brian's values used in his code - try these values if difficult to see right effect.
	/*m_AmbientColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_DiffuseColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_SpecularColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_SpecularPower = 10.0f;*/

	m_ShaderProgram = -1;
	m_Type = "Material";
	m_AmbientColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_DiffuseColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_SpecularColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_SpecularPower = 2.0f;
	m_DiffuseMap = 0;
	m_SpecularMap = 0;
	m_BumpMap = 0;
}

Material::~Material()
{

}

void Material::destroy()
{
	glDeleteProgram(m_ShaderProgram);
	//glDeleteTextures(1, &m_DiffuseMap);
	//glDeleteTextures(1, &m_SpecularMap);
	//glDeleteTextures(1, &m_BumpMap);
}

void Material::Bind()
{
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseMap);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_SpecularMap);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_BumpMap);
	
	GLint vertexPosLocation = glGetAttribLocation(m_ShaderProgram, "vertexPosition");
	GLint vertexNormalsLocation = glGetAttribLocation(m_ShaderProgram, "vertexNormals");
	GLint vertexTexLocation = glGetAttribLocation(m_ShaderProgram, "vertexTexCoords");
	GLint vertexColoursLocation = glGetAttribLocation(m_ShaderProgram, "vertexColours");
	GLint vertexTangentsLocation = glGetAttribLocation(m_ShaderProgram, "vertexTangents");
	GLint vertexBinormalsLocation = glGetAttribLocation(m_ShaderProgram, "vertexBinormals");

	glBindAttribLocation(m_ShaderProgram, vertexPosLocation, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, vertexNormalsLocation, "vertexNormals");
	glBindAttribLocation(m_ShaderProgram, vertexTexLocation, "vertexTexCoords");
	glBindAttribLocation(m_ShaderProgram, vertexColoursLocation, "vertexColours");
	glBindAttribLocation(m_ShaderProgram, vertexTangentsLocation, "vertexTangents");
	//glBindAttribLocation(m_ShaderProgram, 5, "vertexBinormals");
	glBindAttribLocation(m_ShaderProgram, vertexBinormalsLocation, "vertexBinormals");

	glEnableVertexAttribArray(vertexPosLocation);
	glVertexAttribPointer(vertexPosLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(vertexNormalsLocation);
	glVertexAttribPointer(vertexNormalsLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	glEnableVertexAttribArray(vertexTexLocation);
	glVertexAttribPointer(vertexTexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec3)));
	glEnableVertexAttribArray(vertexColoursLocation);
	glVertexAttribPointer(vertexColoursLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec3) + sizeof(vec2)));
	glEnableVertexAttribArray(vertexTangentsLocation);
	glVertexAttribPointer(vertexTangentsLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec3) + sizeof(vec2) + sizeof(vec4)));
	glEnableVertexAttribArray(vertexBinormalsLocation);
	glVertexAttribPointer(vertexBinormalsLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec3) + sizeof(vec2) + sizeof(vec4) + sizeof(vec3)));
}

//GLint BaseMaterial::getUniformLocation(const string& name)
//{
//	/*GLint MVPLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());
//	return MVPLocation;*/
//	return glGetUniformLocation(m_ShaderProgram, name.c_str());
//}

vec4& Material::getAmbientColour()
{
	return m_AmbientColour;
}

void Material::setAmbientColour(float r, float g, float b, float a)
{
	m_AmbientColour = vec4(r, g, b, a);
}

vec4& Material::getDiffuseColour()
{
	return m_DiffuseColour;
}

void Material::setDiffuseColour(float r, float g, float b, float a)
{
	m_DiffuseColour = vec4(r, g, b, a);
}

vec4& Material::getSpecularColour()
{
	return m_SpecularColour;
}

void Material::setSpecularColour(float r, float g, float b, float a)
{
	m_SpecularColour = vec4(r, g, b, a);
}

float Material::getSpecularPower()
{
	return m_SpecularPower;
}

void Material::setSpecularPower(float power)
{
	m_SpecularPower = power;
}

GLuint Material::getDiffuseMap()
{
	return m_DiffuseMap;
}

void Material::loadDiffuseMap(const std::string& filename)
{
	//m_DiffuseMap = loadTextureFromFile(filename);
	m_DiffuseMap = TextureManager::getManager().getTexture(filename);
}

GLuint Material::getSpecularMap()
{
	return m_SpecularMap;
}

void Material::loadSpecularMap(const std::string& filename)
{
	//m_SpecularMap = loadTextureFromFile(filename);
	m_SpecularMap = TextureManager::getManager().getTexture(filename);
}

GLuint Material::getBumpMap()
{
	return m_BumpMap;
}

void Material::loadBumpMap(const std::string& filename)
{
	//m_BumpMap = loadTextureFromFile(filename);
	m_BumpMap = TextureManager::getManager().getTexture(filename);
}

