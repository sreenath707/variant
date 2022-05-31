#pragma once


namespace Variant {
	class Texture
	{
	private:
		unsigned int m_rendererid;
	public:
		Texture(std::string path);
		void Bind();
	};

}

