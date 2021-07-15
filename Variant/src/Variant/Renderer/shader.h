#pragma once
#include<glm/glm.hpp>

namespace Variant {
	class shader
	{
	private:
		unsigned int m_rendererId;
	public:
		shader(std::string& vertexSrc , std::string& fragmentSrc);
		~shader();
		void Bind();
		void UnBind();
		void uploadUniformMat4(std::string uniformName, const glm::mat4& matrix);

	};
}
