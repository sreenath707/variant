#pragma once
#include "RendererAPI.h"

namespace Variant{
	class RendererCommand
	{
	private:
		static RendererAPI* s_rendererAPI;
	public:
		static void drawIndexed(std::shared_ptr<vertexArray> v_vertexArray, int count =0)
		{
			s_rendererAPI->drawIndexed(v_vertexArray, count);
		}
		static void setColor(glm::vec4 color)
		{
			s_rendererAPI->setColor(color);
		}
		static void clearColor()
		{
			s_rendererAPI->clearColor();
		}
		static void setViewPort(float width, float height)
		{
			s_rendererAPI->setViewPort(width, height);
		}
	};
}