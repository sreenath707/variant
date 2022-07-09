#include "vrpch.h"
#include "OpenGLBuffer.h"

namespace Variant {
	 OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices ,unsigned int size)
		:m_rendererId(0)
	{
		glGenBuffers(1, &m_rendererId);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
    OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int size)
       :m_rendererId(0)
    {
       glGenBuffers(1, &m_rendererId);
       Bind();
       glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
    }

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
	}
	void OpenGLVertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
    
    void OpenGLVertexBuffer::uploadData(void* data,unsigned int size)
    {
        Bind();
        glBufferSubData(GL_ARRAY_BUFFER,0,size,data);
    }

	OpenGLIndexBuffer::OpenGLIndexBuffer(void* indices, unsigned int count)
		:m_count(count)
	{

        glGenBuffers(1, &m_rendererId);
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
