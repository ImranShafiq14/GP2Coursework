#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class GameObject;

class Component
{
	public:
		Component();
		virtual ~Component();
		virtual void init();
		virtual void update();
		virtual void render();
		virtual void destroy();
		const std::string& getType();
		void toggleActive();
		bool isActive();

		GameObject * getParent();

		void setParent(GameObject * parent);
	protected:
		std::string m_Type;
		bool m_Active;
		GameObject *m_Parent;
	private:
};

#endif