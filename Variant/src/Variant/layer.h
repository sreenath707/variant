#pragma once
#include "Events/Event.h"
namespace Variant {
	class layer
	{
		std::string m_name;
	public:
		layer(std::string name)
		:m_name(name){}
		virtual ~layer(){}

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnImGuiRender() = 0;
		virtual void OnEvent(Event& event)=0;
		virtual std::string getName() { return m_name; }

	};
}

