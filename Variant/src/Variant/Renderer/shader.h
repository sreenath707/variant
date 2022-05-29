#pragma once
#include<glm/glm.hpp>
#include <glad/glad.h>

namespace Variant {
	class shader
	{
	private:
		unsigned int m_rendererId;
		std::unordered_map<GLenum, std::string> m_shaders;
	public:
		shader(std::string filepath);
		shader(std::string& vertexSrc , std::string& fragmentSrc);
		~shader();
		void Bind();
		void UnBind();
		void compile(std::string& vertexSrc, std::string& fragmentSrc);
		void uploadUniformMat4(std::string uniformName, const glm::mat4& matrix);
		void uploadUniformInt(std::string uniformName, int num);
		void uploadUniformVec4(std::string uniformName, glm::vec4 vec);

	};
}
