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
		
		void addRef()
		{
			m_UsageCount++;
		}

		int getUsageCount()
		{
			return m_UsageCount;
		}

		const std::string& getType();
		const std::string& getName();
		void toggleActive();
		bool isActive();

		GameObject * getParent();

		void setParent(GameObject * parent);
		void setName(const std::string& name);
	protected:
		std::string m_Type;
		std::string m_Name;
		bool m_Active;
		GameObject *m_Parent;

		int m_UsageCount;
	private:
};

#endif