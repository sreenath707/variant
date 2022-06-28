#pragma once
#include "vrpch.h"
#include "glad/glad.h"
#include "log.h"
#include <GLFW/glfw3.h>
#include "Variant/Events/Event.h"
#include "Variant/Events/ApplicationEvent.h"


namespace Variant {
	using windowCallFn = std::function<void(Event&)>;
	class Window
	{
	protected:
		GLFWwindow* m_window;
		
	public:
		virtual  ~Window() {}

		virtual unsigned int getheight() = 0;
		virtual  unsigned int getwidth() = 0;
		virtual void setEventCallBack(windowCallFn callback) = 0;
		virtual void update() = 0;
		inline GLFWwindow* GetWindow() { return m_window; }
		static Window* create();
		inline GLFWwindow* getGlfwWindow() { return m_window; }
	};

}
