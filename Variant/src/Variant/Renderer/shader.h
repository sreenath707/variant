#pragma once

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

	};
}
