#pragma once

#include "Event.h"

namespace Variant {

	class mouseClickEvent :public Event
	{
		int m_button;
	public:
		mouseClickEvent(int button)
			:m_button(button) {}
		std::string getName()override { return "mouseClicked"; }
		EventType getEventType()override { return EventType::MouseButtonPressed; }
		std::string ToString()override
		{
			std::stringstream ss;
			ss << "mouseClicked : " << m_button;
			return ss.str();
		}
		static EventType StaticEventType() { return EventType::MouseButtonPressed; }
		int getEventCategery()override { return (EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton); }
	};
	class mouseReleaseEvent :public Event
	{
		int m_button;
	public:
		mouseReleaseEvent(int button)
			:m_button(button) {}
		std::string getName()override { return "mouseReleased"; }
		EventType getEventType()override { return EventType::MouseButtonReleased; }
		std::string ToString()override
		{
			std::stringstream ss;
			ss << "mouseReleased: " << m_button;
			return ss.str();
		}
		static EventType StaticEventType() { return EventType::MouseButtonReleased; }
		int getEventCategery()override { return (EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton); };

	};

	class mousePosEvent : public Event
	{
		double x_pos, y_pos;
	public:
		mousePosEvent(double xPos,double yPos)
			:x_pos(xPos),y_pos(yPos){}
		std::string getName()override { return "mousePosition"; }
		EventType getEventType()override { return EventType::MouseMoved; }
		std::string ToString()override
		{
			std::stringstream ss;
			ss << "x-position : " << x_pos << " y-position : " << y_pos;
			return ss.str();
		}
		static EventType StaticEventType() { return EventType::MouseMoved; }
		int getEventCategery()override { return (EventCategoryMouse); };

	};

	class mouseScrollEvent :public Event
	{
		double x_offset, y_offset;
	public:
		mouseScrollEvent(double xPos, double yPos)
			:x_offset(xPos), y_offset(yPos) {}
		std::string getName()override { return "mouseScroll"; }
		EventType getEventType()override { return EventType::MouseScrolled; }
		std::string ToString()override
		{
			std::stringstream ss;
			ss << "x-offset : " << x_offset << " y-offset : " << y_offset;
			return ss.str();
		}
		static EventType StaticEventType() { return EventType::MouseScrolled; }
		int getEventCategery()override { return (EventCategoryMouse); };
	};
}