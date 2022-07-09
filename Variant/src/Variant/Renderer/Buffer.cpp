#include "vrpch.h"
#include "Buffer.h"
#include "OpenGL/OpenGLBuffer.h"
#include "RendererAPI.h"

namespace Variant {
	vertexBuffer* vertexBuffer::Create(void* vertices, unsigned int size)
	{
		switch (RendererAPI::getAPI())
		{
		case RendererAPI::API::None: VR_core_error("None is not supported!");
										return nullptr;
										break;
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
			break;
		default:
			return nullptr;
		}
	}

    vertexBuffer* vertexBuffer::Create(unsigned int size)
    {
        switch (RendererAPI::getAPI())
        {
        case RendererAPI::API::None: VR_core_error("None is not supported!");
                                        return nullptr;
                                        break;
        case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(size);
            break;
        default:
            return nullptr;
        }
    }
	
	indexBuffer* indexBuffer::Create(void* indices, unsigned int size)
	{
		switch (RendererAPI::getAPI())
		{
		case RendererAPI::API::None: VR_core_error("None is not supported!");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
			break;
		default:
			return nullptr;
		}
		
	}

}

