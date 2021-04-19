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
}

