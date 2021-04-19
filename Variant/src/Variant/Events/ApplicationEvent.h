#pragma once
#include "Event.h"

namespace Variant{
	class WindowCloseEvent :public Event
	{
	public:
		int getEventCategery()override { return (EventCategoryApplication); }
		static EventType StaticEventType() { return EventType::WindowClose; }
		std::string getName()override { return "WindowClose"; }
		EventType getEventType()override { return EventType::WindowClose; }
		std::string ToString()override
		{
			std::stringstream ss;
			ss << getName();
			return ss.str();
		}

	};

	class WindowResizeEvent :public Event
	{
		int m_width, m_height;
	public:
		WindowResizeEvent(int width,int height)
			:m_width(width),m_height(height){}
		int getEventCategery()override { return (EventCategoryApplication); }
		static EventType StaticEventType() { return EventType::WindowResize; }
		std::string getName()override { return "WindowResize"; }
		EventType getEventType()override { return EventType::WindowResize; }
		std::string ToString()override
		{
			std::stringstream ss;
			ss << getName() << " width :" << m_width << " height :" << m_height;
			return ss.str();
		}
	};
}

