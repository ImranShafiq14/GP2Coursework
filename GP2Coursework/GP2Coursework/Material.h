#ifndef MATERIAL_H
#define MATERIAL_H

#include "Component.h"
#include <string>
#include <GL\glew.h>

#include <glm/glm.hpp>
using glm::vec4;

using namespace std;

class BaseMaterial :public Component{
public:
	BaseMaterial()
	{
		m_Type = "BaseMaterial";
	};
	virtual ~BaseMaterial(){}

	virtual void bind(){};
	virtual void unbind(){};

	bool loadShader(const std::string& vsFilename, const std::string& fsFilename);
	GLint getUniformLocation(const std::string& name);
protected:
	GLuint m_ShaderProgram;
};

class Material : public BaseMaterial
{
public:
	Material();
	~Material();

	void destroy();
	bool loadShader(const string& vertexShader, const string& fragmentShader);
	void Bind();
	GLint getUniformLocation(const string& name);

	vec4& getAmbientColour();
	void setAmbientColour(float r, float g, float b, float a);

	vec4& getDiffuseColour();
	void setDiffuseColour(float r, float g, float b, float a);

	vec4& getSpecularColour();
	void setSpecularColour(float r, float g, float b, float a);
	
	float getSpecularPower();
	void setSpecularPower(float power);

	GLuint getDiffuseMap();
	void loadDiffuseMap(const std::string& filename);

	GLuint getSpecularMap();
	void loadSpecularMap(const std::string& filename);

	GLuint getBumpMap();
	void loadBumpMap(const std::string& filename);
private:
	GLuint m_ShaderProgram;

	vec4 m_AmbientColour;
	vec4 m_DiffuseColour;
	vec4 m_SpecularColour;
	float m_SpecularPower;

	GLuint m_DiffuseMap;
	GLuint m_SpecularMap;
	GLuint m_BumpMap;
};

#endif 