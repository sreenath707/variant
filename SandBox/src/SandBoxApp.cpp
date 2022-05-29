#include "..\..\Variant\src\Variant\core\Application.h"
#include <variant.h>
#include <glm/glm.hpp>


class exampleLayer : public Variant::layer
{
private:

	Variant::OrthographicCameraController m_cameraController;


public:

	exampleLayer()
		:layer("exampleLayer"), m_cameraController(16.0f / 9.0f, false)
	{
		Variant::Renderer2D::Init();
	}

	virtual void OnAttach()override
	{
		
	}
	void OnDetach()override
	{

	}
	void OnImGuiRender()override
	{

	}
	void OnEvent(Variant::Event& event)
	{
		m_cameraController.OnEvent(event);
	}
	virtual void OnUpdate(Variant::deltaTime dt)
	{
		
		m_cameraController.OnUpdate(dt);

		Variant::Renderer2D::BeginScene(m_cameraController.getCamera());
		Variant::RendererCommand::clearColor();
		Variant::RendererCommand::setColor({ 0.1,0.1,0.1,1.0 });
		Variant::Renderer2D::DrawQuad({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f }, 0, { 1.0f,0.2f,0.3f,1.0f });	
		Variant::Renderer2D::DrawQuad({ 0.7f,-0.2f,0.0f }, { 0.7f,1.0f }, 0, { 0.3f,0.1f,1.0f,1.0f });
		Variant::Renderer2D::EndScene();
	}
};


class SandBox : public Variant::Application
{


public:
	SandBox()
	{
		pushLayer(new exampleLayer());
	}

	~SandBox()
	{

	}
};


Variant::Application* Variant::CreateApplication()
{
	return new SandBox();
}


