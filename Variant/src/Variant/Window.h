#pragma once
#include "vrpch.h"
#include "log.h"
#include "GLFW/glfw3.h"

namespace Variant {

	class Window
	{
	protected:
		GLFWwindow* m_window;
		unsigned int m_height, m_width;
		std::string m_name;
		
	public:
		virtual  ~Window() {}

		virtual unsigned int getheight() = 0;
		virtual  unsigned int getwidth() = 0;
		virtual void update() = 0;
		static Window* create();
	};

}