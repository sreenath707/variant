#include "vrpch.h"
#include "OpenGLBuffer.h"

namespace Variant {
	 OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices ,unsigned int size)
		:m_rendererId(0)
	{
		glCreateBuffers(1, &m_rendererId);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	 OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int size)
		 :m_rendererId(0)
	 {
		 glCreateBuffers(1, &m_rendererId);
		 Bind();
		 glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	 }


	 void OpenGLVertexBuffer::setData(void* data, unsigned int size)
	 {
		 this->Bind();
		 glBufferSubData(m_rendererId, 0, size, data);
	 }

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
	}
	void OpenGLVertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	OpenGLIndexBuffer::OpenGLIndexBuffer(void* indices, unsigned int count)
		:m_count(count)
	{

		glCreateBuffers(1, &m_rendererId);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), indices, GL_STATIC_DRAW);

	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
	}
	void OpenGLIndexBuffer::unbind()
	{
	}
}