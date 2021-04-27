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

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event){}
		virtual std::string getName() { return m_name; }

	};
}

