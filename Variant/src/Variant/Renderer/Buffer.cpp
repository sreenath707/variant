#include "vrpch.h"
#include "Buffer.h"
#include "OpenGL/OpenGLBuffer.h"

namespace Variant {
	vertexBuffer* vertexBuffer::Create(void* vertices, unsigned int size)
	{
		return new OpenGLVertexBuffer(vertices,size);
	}


	
	indexBuffer* indexBuffer::Create(void* indices, unsigned int size)
	{
		return new OpenGLIndexBuffer(indices, size);
	}

}

