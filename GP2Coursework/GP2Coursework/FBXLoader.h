#ifndef FBXLoader_H
#define FBXLoader_H

#include <fbxsdk.h>

#include <string>
#include "Vertex.h"

class GameObject;
class Mesh;

GameObject * loadFBXFromFile(const std::string& filename); 

void processNode(FbxNode *node, GameObject *rootGo);
void processAttribute(FbxNodeAttribute * attribute, GameObject * go);

//void processMesh(FbxMesh * mesh, GameObject *go);
Mesh * processMesh(FbxMesh * mesh);

void processMeshNormals(FbxMesh * mesh, Vertex * verts, int numVerts);

void processMeshTextureCoords(FbxMesh * mesh, Vertex * verts, int numVerts);

void calculateTagentAndBinormals(Vertex * verts, int numVerts, int * indices, int numIndices);

#endif