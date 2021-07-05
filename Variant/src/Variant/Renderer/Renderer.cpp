#include"vrpch.h"
#include "Renderer.h"
#include "RendererCommand.h"

namespace Variant {
	void Renderer::BeginScene()
	{

	}
	void Renderer::EndScene()
	{

	}
	void Renderer::submit(std::shared_ptr<vertexArray>& v_vertexArray)
	{
		v_vertexArray->Bind();
		RendererCommand::drawIndexed(v_vertexArray);
	}
}