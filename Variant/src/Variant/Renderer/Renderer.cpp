#include"vrpch.h"
#include "Renderer.h"
#include "RendererCommand.h"

namespace Variant {
	Renderer::sceneData* Renderer::s_sceneData = new Renderer::sceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_sceneData->viewprojMatrix = camera.getProjectionView();
	}
	void Renderer::EndScene()
	{

	}
	void Renderer::submit(std::shared_ptr<vertexArray>& v_vertexArray, std::shared_ptr<shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->uploadUniformMat4("u_viewProjection", s_sceneData->viewprojMatrix);
		shader->uploadUniformMat4("u_transform", transform);
		v_vertexArray->Bind();
		RendererCommand::drawIndexed(v_vertexArray);
	}
}
