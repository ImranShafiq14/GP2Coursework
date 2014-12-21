#include "Component.h"
#include "GameObject.h"


Component::Component()
{
	m_Type = "Component";
	m_Active = true;
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

GameObject * Component::getParent()
{
	return m_Parent;
}