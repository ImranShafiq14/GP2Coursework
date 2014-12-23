#include "GameObject.h"
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Transform.h"
#include "Light.h"


GameObject::GameObject()
{
	m_Name = "GameObject";
	m_Mesh = NULL;
	m_Material = NULL;
	m_Camera = NULL;
	m_Transform = NULL;
	m_Light = NULL;
	m_Parent = NULL;
}

GameObject::~GameObject()
{

}

void GameObject::init()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->init();
	}
	
	for (auto iterChildren = m_Children.begin(); iterChildren != m_Children.end(); iterChildren++)
	{
		(*iterChildren)->init();
	}
}

void GameObject::update()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->update();
	}

	for (auto iterChildren = m_Children.begin(); iterChildren != m_Children.end(); iterChildren++)
	{
		(*iterChildren)->update();
	}
}

void GameObject::render()
{
	for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->render();
	}

	for (auto iterChildren = m_Children.begin(); iterChildren != m_Children.end(); iterChildren++)
	{
		(*iterChildren)->render();
	}
}

void GameObject::destroy()
{
	auto iter = m_Components.begin();
	while (iter != m_Components.end())
	{
		if ((*iter))
		{
			(*iter)->destroy();
			if ((*iter)->getUsageCount() == 0)
			{
				delete (*iter);
				(*iter) = NULL;
			}
			iter = m_Components.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	m_Components.clear();

	auto iterChildren = m_Children.begin();
	while (iterChildren != m_Children.end())
	{
		(*iterChildren)->destroy();
		if ((*iterChildren))
		{
			delete(*iterChildren);
			(*iterChildren) = NULL;
			iterChildren = m_Children.erase(iterChildren);
		}
		else
		{
			iterChildren++;
		}
	}
	m_Children.clear();
}

void GameObject::addComponent(Component * component)
{
	component->setParent(this);
	component->addRef();
	m_Components.push_back(component);
}

void GameObject::setName(const std::string& name)
{
	m_Name = name;
}

const std::string& GameObject::getName()
{
	return m_Name;
}

void GameObject::setMesh(Mesh * mesh)
{
	m_Mesh = mesh;
	addComponent(m_Mesh);
}

Mesh * GameObject::getMesh()
{
	return m_Mesh;
}

void GameObject::setMaterial(BaseMaterial * material)
{
	m_Material = material;
	addComponent(m_Material);
}

BaseMaterial * GameObject::getMaterial()
{
	return m_Material;
}

void GameObject::setCamera(Camera * camera)
{
	m_Camera = camera;
	addComponent(m_Camera);
}

Camera * GameObject::getCamera()
{
	return m_Camera;
}

void GameObject::setTransform(Transform * transform)
{
	m_Transform = transform;
	addComponent(m_Transform);
}

Transform * GameObject::getTransform()
{
	return m_Transform;
}

void GameObject::setLight(Light * light)
{
	m_Light = light;
	addComponent(m_Light);
}

Light * GameObject::getLight()
{
	return m_Light;
}

void GameObject::setParent(GameObject* parent)
{
	m_Parent = parent;
}

GameObject* GameObject::getParent()
{
	return m_Parent;
}

void GameObject::addChild(GameObject* child)
{
	child->setParent(this);
	m_Children.push_back(child);
}

int GameObject::getChildCount()
{
	return m_Children.size();
}

GameObject* GameObject::getChild(int index)
{
	if (index < m_Children.size())
	{
		return m_Children[index];
	}
	else
	{
		return NULL;
	}
}

Component * GameObject::getComponentByType(const std::string& type)
{
	Component *found = NULL;
	//std::find_if(m_Components.begin(),m_Components.end(),[type](Component &n){return n.getType()==type;});
	return found;
}

Component * GameObject::getComponentByName(const std::string& name)
{
	Component *found = NULL;
	//std::find_if(m_Components.begin(),m_Components.end(),[type](Component &n){return n.getType()==type;});
	return found;
}

