#include "..\..\Variant\src\Variant\core\Application.h"
#include <variant.h>
#include <glm/glm.hpp>


class exampleLayer : public Variant::layer
{
private:
	std::shared_ptr<Variant::vertexBuffer> m_vertexBuffer;
	std::shared_ptr<Variant::indexBuffer> m_indexBuffer;
	std::shared_ptr<Variant::vertexArray> m_vertexArray;
	std::shared_ptr<Variant::shader> m_shader;
	Variant::OrthographicCamera m_camera;
	glm::vec3 m_cameraPosition = { 0.0,0.0,0.0 };


public:

	exampleLayer()
	:layer("exampleLayer"),m_camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{

		m_vertexArray.reset(Variant::vertexArray::Create());

		float vertices[3 * 6] =
		{
			-0.5f,-0.5f,0.0f     ,1.0,0,0,
			 0.5f,-0.5f,0.0f     ,0,1.0,0,
			 0.0f,0.5f,0.0f      ,0,0,1.0
		};

		m_vertexBuffer.reset(Variant::vertexBuffer::Create(vertices, sizeof(vertices)));
		m_vertexBuffer->Bind();

		Variant::BufferLayout layout = {
			{Variant::shaderDataType::Float3,"position"},
			{Variant::shaderDataType::Float3,"color"}
		};

		m_vertexBuffer->setLayout(layout);
		m_vertexArray->addVertexBuffer(m_vertexBuffer);


		unsigned int indices[3] = { 0,1,2 };
		m_indexBuffer.reset(Variant::indexBuffer::Create(indices, 3));
		m_indexBuffer->Bind();
		m_vertexArray->SetIndexBuffer(m_indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			layout(location=0) in vec3 a_position;
			layout(location=1) in vec3 a_color;
			uniform mat4 u_viewProjection;

			out vec3 v_position;
			void main()
			{
				v_position = a_color;
				gl_Position = u_viewProjection * vec4(a_position,1.0);
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

		m_shader.reset(new Variant::shader(vertexSrc, fragmentSrc));
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

	}
	virtual void OnUpdate(Variant::deltaTime dt)
	{
		m_shader->Bind();

		Variant::RendererCommand::setColor({ 0.1f, 0.1f, 0.1f, 1 });
		Variant::RendererCommand::clearColor();

		if (Variant::input::isKeyPressed(VR_KEY_A))
			m_cameraPosition.x -= 1.0f * float(dt);
		else if (Variant::input::isKeyPressed(VR_KEY_D))
			m_cameraPosition.x += 1.0f * float(dt);

		if (Variant::input::isKeyPressed(VR_KEY_W))
			m_cameraPosition.y += 1.0f * float(dt);
		else if (Variant::input::isKeyPressed(VR_KEY_S))
			m_cameraPosition.y -= 1.0f * float(dt);

		Variant::Renderer::BeginScene(m_camera);

		m_camera.setPosition(m_cameraPosition);

		Variant::Renderer::submit(m_vertexArray, m_shader);
		Variant::Renderer::EndScene();
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


