#pragma once
#include "vertexArray.h"
#include "glm/vec4.hpp"

namespace Variant {

	class RendererAPI
	{

	public:
		enum class API
		{
			None = 0, OpenGL
		};

		static API s_API;

		inline static RendererAPI::API getAPI() { return s_API; }
		
			virtual void drawIndexed(std::shared_ptr<vertexArray> v_vertexArray, int count=0) = 0;
			virtual void setColor(glm::vec4 color) = 0;
			virtual void clearColor()=0;
			virtual void setViewPort(float width, float height) = 0;
	};

}
