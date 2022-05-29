#include "vrpch.h"
#include "Renderer2D.h"
#include "vertexArray.h"
#include "shader.h"
#include "RendererCommand.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Variant {

	struct RendererData {
		std::shared_ptr<Variant::vertexBuffer> vertexBuffer;
		std::shared_ptr<Variant::indexBuffer> indexBuffer;
		std::shared_ptr<Variant::vertexArray> vertexArray;
		std::shared_ptr<Variant::shader> shader;
	};

	RendererData* s_rendererData = new RendererData();

	void Renderer2D::Init()
	{
		
		s_rendererData->vertexArray.reset(Variant::vertexArray::Create());

		float vertices[4 * 3] =
		{
			0.5f,0.5f,0.0f,
			-0.5f,0.5f,0.0f,
			-0.5f,-0.5f,0.0f,
			 0.5f,-0.5f,0.0f
		};

		s_rendererData->vertexBuffer.reset(Variant::vertexBuffer::Create(vertices, sizeof(vertices)));
		s_rendererData->vertexBuffer->Bind();

		Variant::BufferLayout layout = {
			{Variant::shaderDataType::Float3,"position"}
		};

		s_rendererData->vertexBuffer->setLayout(layout);
		s_rendererData->vertexArray->addVertexBuffer(s_rendererData->vertexBuffer);


		unsigned int indices[6] = { 0,1,2,2,3,0 };
		s_rendererData->indexBuffer.reset(Variant::indexBuffer::Create(indices, 6));
		s_rendererData->indexBuffer->Bind();
		s_rendererData->vertexArray->SetIndexBuffer(s_rendererData->indexBuffer);

		s_rendererData->shader.reset(new Variant::shader("Assets/Shaders/shader.glsl"));
	}
	void Renderer2D::ShutDown()
	{
		delete s_rendererData;
	}
	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		s_rendererData->shader->Bind();
		s_rendererData->shader->uploadUniformMat4("u_viewProjection", camera.getProjectionView());
	}
	void Renderer2D::EndScene()
	{
	}
	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec2 size,float rotation, glm::vec4 color)
	{
		s_rendererData->vertexArray->Bind();
		s_rendererData->shader->Bind();
		glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0), position) 
			* glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0.0f,0.0f,1.0f)) 
			* glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
		s_rendererData->shader->uploadUniformMat4("u_transform", transformMatrix);
		s_rendererData->shader->uploadUniformVec4("u_color", color);
		RendererCommand::drawIndexed(s_rendererData->vertexArray);
	}
}