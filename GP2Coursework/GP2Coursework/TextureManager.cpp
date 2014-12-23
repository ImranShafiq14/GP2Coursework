#include "TextureManager.h"

//Constructor for TextureManager - IS
TextureManager::TextureManager()
{
	m_LoadedTexturesMap.clear();
	m_LoadedTexturesVector.clear();
}

//Deconstructor for TextureManager - IS
TextureManager::~TextureManager()
{

}

//Clears all of the textures held by the class - IS
void TextureManager::clear()
{
	glDeleteTextures((int)m_LoadedTexturesVector.size(), &m_LoadedTexturesVector[0]);
	m_LoadedTexturesVector.clear();
	m_LoadedTexturesMap.clear();
}

//adds texture to texture manager - IS
GLuint TextureManager::getTexture(const std::string &name)
{
	GLuint textureID = 0;

	//get the name, strip out path and extension, leave only have name of texture
	long lastSlashPos = name.find_last_of('/');
	long dotPos = name.find_last_of('.');
	
	std::string nameID = name.substr(lastSlashPos + 1, dotPos - 1);
	
	auto iter = m_LoadedTexturesMap.find(nameID);
	if (iter != m_LoadedTexturesMap.end())
	{
		textureID = iter->second;
	}
	else
	{
		//load texture
		textureID = loadTextureFromFile(name);
		m_LoadedTexturesVector.push_back(textureID);
		m_LoadedTexturesMap[nameID] = textureID;
	}
	
	return textureID;
}