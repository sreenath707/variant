#pragma once
#include "vertexArray.h"
namespace Variant {
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void submit(std::shared_ptr<vertexArray>& v_vertexArray);
	};
}
