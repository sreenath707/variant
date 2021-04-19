#pragma once
#include "core.h"
#include "GLFW/glfw3.h"
#include "Window.h"

namespace Variant {

	class VR_API Application
	{
		bool m_running;
		std::unique_ptr<Window> m_Window;
	public:
		Application();

		virtual ~Application();

		void run();
		void OnEvent(Event& e);
		bool OnWindowClose(Event& e);

	};

	Application* CreateApplication();

}
