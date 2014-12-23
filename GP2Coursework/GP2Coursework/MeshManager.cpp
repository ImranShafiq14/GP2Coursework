#include "MeshManager.h"

MeshManager::MeshManager()
{

}

MeshManager::~MeshManager()
{

}

void MeshManager::clear()
{
	auto iter = m_LoadedMeshesVector.begin();
	while (iter != m_LoadedMeshesVector.end())
	{
		if ((*iter))
		{
			(*iter)->destroy();
			if ((*iter)->getUsageCount() == 0)
			{
				delete (*iter);
				(*iter) = NULL;
			}
			iter = m_LoadedMeshesVector.erase(iter);
		}
	}

	m_LoadedMeshesVector.clear();
	m_LoadedMeshesMap.clear();
}

Mesh * MeshManager::getMesh(const std::string &name)
{
	Mesh *pMesh = NULL;

	auto iter = m_LoadedMeshesMap.find(name);
	if (iter != m_LoadedMeshesMap.end())
	{
		pMesh = iter->second;
	}
	return pMesh;
}

void MeshManager::addMesh(const std::string &name, Mesh *pMesh)
{
	m_LoadedMeshesMap[name] = pMesh;
	m_LoadedMeshesVector.push_back(pMesh);
}