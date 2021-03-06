#pragma once
#include "core.h"
#include "Window.h"
#include "layerStack.h"
#include "Variant/imgui/imguiLayer.h"
#include "Variant/Renderer/Buffer.h"
#include "Variant/Renderer/vertexArray.h"
#include "Variant/Renderer/shader.h"
#include "Variant/Renderer/OrthographicCamera.h"
#include "Variant/core/deltaTime.h"

namespace Variant {
	
	class Application
	{
		static Application* m_instance;
		bool m_running;
		std::unique_ptr<Window> m_Window;
		layerStack m_layerstack;
		std::unique_ptr<imguiLayer> ImLayer;
		float m_currTime=0;
		bool OnWindowResize(WindowResizeEvent& e);

		
	public:
		Application();

		virtual ~Application();

		void run();
		void OnEvent(Event& e);
		bool OnWindowClose(Event& e);
		void pushLayer(layer* layer);
		void popLayer(layer* layer);
		void pushOverlay(layer* layer);
		void popOverlay(layer* layer);
		inline static Application& Get() { return *m_instance; }
		inline Window& GetWindow() { return *m_Window; }

	};

	Application* CreateApplication();

}
