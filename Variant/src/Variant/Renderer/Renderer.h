#pragma once
#include "vertexArray.h"
#include "OrthographicCamera.h"
#include "shader.h"
#include <glm/glm.hpp>

namespace Variant {
	
	
	
	class Renderer
	{
	public:
		struct sceneData
		{
			glm::mat4 viewprojMatrix;
		};

		static sceneData* s_sceneData;

	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void submit(std::shared_ptr<vertexArray>& v_vertexArray, std::shared_ptr<shader>& shader);

	};
}
