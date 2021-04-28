#pragma once
#include "Variant/core.h"
#include "vrpch.h"

//CATEGERIES SHOULD BE IMPLIMENTED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

namespace Variant {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategery
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	class Event
	{
	public:
		bool isHandled;
		Event()
			:isHandled(false){}
		virtual ~Event() = default;

		virtual std::string getName() = 0;
		virtual EventType getEventType() = 0;
		virtual std::string ToString() =0;
		virtual int getEventCategery()= 0;

	};

	class EventDispatcher
	{
		Event& m_event;
	public:
		EventDispatcher(Event& e)
			:m_event(e){}
		template<typename T,typename F>
		void dispatch(const F& func)
		{
			if (T::StaticEventType() == m_event.getEventType())
			{
				m_event.isHandled |= func(static_cast<T&>(m_event));
			}
		}
	};

	inline std::ostream& operator<<(std::ostream& os, Event& e)
	{
		return os << e.ToString();
	}
}