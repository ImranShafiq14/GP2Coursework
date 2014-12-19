#ifndef TextureManager_h
#define TextureManager_h

#include "Texture.h"

#include <GL/glew.h>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#elif WIN32
#include <SDL_opengl.h>
#endif

#include <string>
#include <map>
#include <vector>


class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	GLuint getTexture(const std::string &name);
	
	void clear();
	
	static TextureManager& getManager()
	{
		static TextureManager manager;
		return manager;
	}
private:
	std::map<std::string, GLuint> m_LoadedTexturesMap;
	std::vector<GLuint> m_LoadedTexturesVector;
};
#endif