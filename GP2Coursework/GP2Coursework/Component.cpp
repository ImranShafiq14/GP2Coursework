#include "Component.h"
#include "GameObject.h"


Component::Component()
{
	m_Type = "Component";
	m_Name = "Component";
	m_Active = true;
	m_Parent = NULL;
	m_UsageCount = 0;
}

Component::~Component()
{

}

void Component::init()
{

}

void Component::update()
{

}

void Component::render()
{

}

void Component::destroy()
{
	m_UsageCount--;
}

const std::string& Component::getType()
{
	return m_Type;
}

bool Component::isActive()
{
	return m_Active;
}

void Component::setParent(GameObject * parent)
{
	m_Parent = parent;
}

void Component::toggleActive()
{
	m_Active != m_Active;
}

const std::string& Component::getName()
{
	return m_Name;
}

void Component::setName(const std::string& name)
{
	m_Name = name;
}

GameObject * Component::getParent()
{
	return m_Parent;
}