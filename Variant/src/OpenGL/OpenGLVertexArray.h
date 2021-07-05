#pragma once

#include "Variant/Renderer/vertexArray.h"

namespace Variant {
	class OpenGLVertexArray : public vertexArray
	{
	private:
		unsigned int m_rendererId;
		std::vector<std::shared_ptr<vertexBuffer>> m_vertexBuffers;
		std::shared_ptr<indexBuffer> m_indexBuffer;
		int m_vertexBufferIndex = 0;


	public:

		OpenGLVertexArray();

		virtual void SetIndexBuffer(std::shared_ptr<indexBuffer>& Buffer) override;
		virtual void addVertexBuffer(std::shared_ptr<vertexBuffer>& Buffer) override;

		virtual std::vector<std::shared_ptr<vertexBuffer>>& getVertexBuffers() override;
		virtual std::shared_ptr<indexBuffer>& getIndexBuffer() override;
		virtual void Bind() override;
		virtual void UnBind() override;


	};
}
