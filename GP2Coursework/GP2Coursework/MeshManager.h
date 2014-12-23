#ifndef MeshManager_h
#define MeshManager_h

#include "Mesh.h"

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

class MeshManager
{
public:
	MeshManager();
	~MeshManager();
	
	Mesh * getMesh(const std::string &name);
	void addMesh(const std::string &name, Mesh *pMesh);
	
	void clear();
	
	static MeshManager& getManager()
	{
		static MeshManager manager;
		return manager;
	}
private:
	std::map<std::string, Mesh*> m_LoadedMeshesMap;
	std::vector<Mesh*> m_LoadedMeshesVector;
};
#endif