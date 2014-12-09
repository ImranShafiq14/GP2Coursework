#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>

using namespace std;

class Component;
class Mesh;
class Material;
class Camera;
class Transform;
class Light;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void init();
	void update();
	void render();
	void destroy();

	const std::string& getName();
	void setName(const std::string& name);
	void addComponent(Component * component);

	void addChild(GameObject* child);
	int getChildCount();

	Mesh * getMesh();
	Material * getMaterial();
	Camera * getCamera();
	Transform * getTransform();
	Light * getLight();

	GameObject* getParent();
	GameObject* getChild(int index);

	void setMesh(Mesh * mesh);
	void setMaterial(Material * material);
	void setCamera(Camera * camera);
	void setTransform(Transform * transform);
	void setLight(Light * light);

	void setParent(GameObject* parent);
protected:
private:
	std::string m_Name;
	vector<Component*> m_Components;
	
	Mesh *m_Mesh;
	Material *m_Material;
	Camera *m_Camera;
	Transform *m_Transform;
	Light *m_Light;

	GameObject* m_Parent;
	vector<GameObject*> m_Children;

};

#endif