#pragma once
#include "Variant/Renderer/OrthographicCamera.h"
#include "Variant/Renderer/Texture.h"

namespace Variant {

	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(glm::vec3 position, glm::vec2 size,float rotation, glm::vec4 color);
		static void DrawTexture(glm::vec3 position, glm::vec2 size, float rotation,std::shared_ptr<Texture>  texture);
	};
}