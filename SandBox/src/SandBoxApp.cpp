#include "..\..\Variant\src\Variant\core\Application.h"
#include <variant.h>
#include <glm/glm.hpp>


class exampleLayer : public Variant::layer
{
private:

	Variant::OrthographicCameraController m_cameraController;
	std::shared_ptr<Variant::Texture> m_texture;


public:

	exampleLayer()
		:layer("exampleLayer"), m_cameraController(16.0f / 9.0f, false)
	{
		Variant::Renderer2D::Init();
		m_texture.reset(new Variant::Texture("Assets/Textures/batman.jpg"));
	}

	virtual void OnAttach()override
	{
		
	}
	void OnDetach()override
	{

	}
	void OnImGuiRender()override
	{
		ImGui::Begin("Transform test");
		ImGui::DockSpaceOverViewport();
		//ImGui::ShowDemoWindow();
		ImGui::End();
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
		Variant::Renderer2D::DrawQuad({ 0.25f,0.0f,0.0f }, { 0.25f,0.25f }, 0, { 1.0f,0.2f,0.3f,1.0f });	
		Variant::Renderer2D::DrawQuad({ -0.25f,-0.25f,0.0f }, { 0.50f,0.25f }, 0, { 1.0f,0.2f,0.3f,1.0f });	
		Variant::Renderer2D::DrawTexture({ 0.7f,-0.2f,0.0f }, { 0.5f,0.5f }, 0, m_texture);
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


