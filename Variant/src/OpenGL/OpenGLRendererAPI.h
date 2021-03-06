#pragma once
#include "Variant/Renderer/RendererAPI.h"

namespace Variant {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void drawIndexed(std::shared_ptr<vertexArray> v_vertexArray, int count)override;
		virtual void setColor(glm::vec4 color) override;
		virtual void clearColor() override;
		virtual void setViewPort(float width, float height) override;

	};
}
