#include "vrpch.h"
#include "Application.h"
#include "input.h"

namespace Variant {
	Application* Application::m_instance = NULL;
	Application::Application()
		:m_running(true)
	{
		m_instance = this;
		m_Window = (std::unique_ptr<Window>)Window::create();
		m_Window->setEventCallBack(std::bind(&Application::OnEvent,this ,std::placeholders::_1));

		ImLayer = std::make_unique<imguiLayer>();


		m_vertexArray.reset(vertexArray::Create());
		
		float vertices[3*6] =
		{
			-0.5f,-0.5f,0.0f     ,1.0,0,0,
			 0.5f,-0.5f,0.0f     ,0,1.0,0,
			 0.0f,0.5f,0.0f      ,0,0,1.0
		};

		m_vertexBuffer.reset(vertexBuffer::Create(vertices,sizeof(vertices)));
		m_vertexBuffer->Bind();

		BufferLayout layout = {
			{shaderDataType::Float3,"position"},
			{shaderDataType::Float3,"color"}
		};

		m_vertexBuffer->setLayout(layout);
		m_vertexArray->addVertexBuffer(m_vertexBuffer);
		

		unsigned int indices[3] = { 0,1,2 }; 
		m_indexBuffer.reset(indexBuffer::Create(indices, sizeof(indices)));
		m_indexBuffer->Bind();
		m_vertexArray->SetIndexBuffer(m_indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			layout(location=0) in vec3 a_position;
			layout(location=1) in vec3 a_color;
			out vec3 v_position;
			void main()
			{
				v_position = a_color;
				gl_Position = vec4(a_position,1.0);
			}

			)";
		std::string fragmentSrc = R"(
			#version 330 core
			layout (location=0) out vec4 color;
			in vec3 v_position;
			void main()
			{
				color = vec4(v_position,1.0);
			}

			)";

		m_shader.reset(new shader(vertexSrc, fragmentSrc));
		

	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		
		for (auto it = m_layerstack.rbegin(); it != m_layerstack.rend(); ++it)
		{
			if (e.isHandled)
			{
				break;
			}
			(*it)->OnEvent(e);
		}
	}

	void Application::run()
	{
		while (m_running)
		{
			
			for (layer* layer : m_layerstack)
			{
				layer->OnUpdate();
			}

			ImLayer->Begin();
			ImLayer->OnImGuiRender();
			ImLayer->End();

			m_Window->update();

			m_shader->Bind();

			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		}
	}

	bool Application::OnWindowClose(Event& e)
	{
		m_running = false;
		return true;
	}

	void Application::pushLayer(layer* layer)
	{
		m_layerstack.pushLayer(layer);
		layer->OnAttach();
	}

	void Application::popLayer(layer* layer)
	{
		m_layerstack.popLayer(layer);
	}

	void Application::pushOverlay(layer* layer)
	{
		m_layerstack.pushOverlay(layer);
		layer->OnAttach();
	}

	void Application::popOverlay(layer* layer)
	{
		m_layerstack.popOverlay(layer);
	}

}

