#pragma once
#include "Variant/Renderer/Buffer.h"
#include "glad/glad.h"

namespace Variant {
	class OpenGLVertexBuffer :public vertexBuffer
	{
		unsigned int m_rendererId;
	public:
		OpenGLVertexBuffer(void* vertices,unsigned int size);
		virtual void Bind()override;
		virtual void unbind()override;
	};

	class OpenGLIndexBuffer : public indexBuffer
	{
		unsigned int m_rendererId;
		unsigned int m_count;
	public:
		OpenGLIndexBuffer(void* indices, unsigned int count);
		virtual void Bind()override;
		virtual void unbind()override;
		inline virtual unsigned int getCount()override { return m_count; }

	};
}
