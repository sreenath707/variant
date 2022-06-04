#pragma once
#include <glm/glm.hpp>

namespace Variant {
	class Texture
	{
	private:
		unsigned int m_rendererid;
	public:
		Texture(std::string path);
		Texture(glm::vec4 color);
		~Texture();
		void Bind();
	};

}

