#pragma once
#include "RendererAPI.h"

namespace Variant{
	class RendererCommand
	{
	private:
		static RendererAPI* s_rendererAPI;
	public:
		static void drawIndexed(std::shared_ptr<vertexArray> v_vertexArray)
		{
			s_rendererAPI->drawIndexed(v_vertexArray);
		}
		static void setColor(glm::vec4 color)
		{
			s_rendererAPI->setColor(color);
		}
		static void clearColor()
		{
			s_rendererAPI->clearColor();
		}
	};
}