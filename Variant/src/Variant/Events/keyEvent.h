#pragma once
#include "Event.h"
#include "vrpch.h"

namespace Variant {
	
	class keyEvent :public Event
	{
	protected:
		keycode m_keycode;
	  protected:
		  keyEvent(uint16_t keycode)
			  :m_keycode(keycode){}
	  public:
		  int getEventCategery()override { return (EventCategoryKeyboard | EventCategoryInput); }

		  keycode getKeyCode()const { return m_keycode; }

	};

	class keyPressedEvent :public keyEvent
	{
		uint16_t m_repeatedCout;
	public:
		keyPressedEvent(keycode code,uint16_t repeatedCount)
		:keyEvent(code),m_repeatedCout(repeatedCount){}
		std::string getName()override { return "keyPressed"; }
		EventType getEventType()override { return EventType::KeyPressed; }
		 std::string ToString()override
		 {
			 std::stringstream ss;
			 ss << "key code : " << m_keycode << " repeat count : " << m_repeatedCout;
			 return ss.str();
		 }
		 static EventType StaticEventType() { return EventType::KeyPressed; }
	};

	class keyReleaseEvent :public keyEvent
	{
	public:
		keyReleaseEvent(keycode code)
		: keyEvent(code){}
		std::string getName()override { return "keyRelease"; }
		EventType getEventType()override { return EventType::KeyReleased; }
		std::string ToString()override
		{
			std::stringstream ss;
			ss << "key code : " << m_keycode;
			return ss.str();
		}
		static EventType StaticEventType() { return EventType::KeyReleased; }
	};

	class keyTypedEvent :public keyEvent
	{
	public:
		keyTypedEvent(keycode code)
			: keyEvent(code) {}
		std::string getName()override { return "KeyTyped"; }
		EventType getEventType()override { return EventType::KeyTyped; }
		std::string ToString()override
		{
			std::stringstream ss;
			ss << "key typed code : " << m_keycode;
			return ss.str();
		}
		static EventType StaticEventType() { return EventType::KeyTyped; }
	};
}