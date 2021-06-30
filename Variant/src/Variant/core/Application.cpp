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
		
		float vertices[9] =
		{
			-0.5f,-0.5f,0.0f,
			 0.5f,-0.5f,0.0f,
			 0.0f,0.5f,0.0f
		};

		m_vertexBuffer.reset(vertexBuffer::Create(vertices,sizeof(vertices)));
		m_vertexBuffer->Bind();

		BufferLayout layout = {
			{shaderDataType::Float3,"position"}
		};

		m_vertexBuffer->setLayout(layout);
		m_vertexArray->addVertexBuffer(m_vertexBuffer);
		

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indices[3] = { 0,1,2 }; 
		m_indexBuffer.reset(indexBuffer::Create(indices, sizeof(indices)));
		m_indexBuffer->Bind();
		m_vertexArray->SetIndexBuffer(m_indexBuffer);
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

