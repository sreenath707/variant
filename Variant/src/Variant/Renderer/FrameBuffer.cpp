#include "vrpch.h"
#include "FrameBuffer.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLFrameBuffer.h"

namespace Variant {
	FrameBuffer* FrameBuffer::Create(float width, float height)
	{
		switch (RendererAPI::getAPI())
		{
		case RendererAPI::API::None: VR_core_error("None is not supported!");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL: return new OpenGLFrameBuffer(width,height);
			break;
		default:
			return nullptr;
		}
	}
}