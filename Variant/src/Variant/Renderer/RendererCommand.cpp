#include "vrpch.h"
#include "RendererCommand.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace Variant {
	RendererAPI* RendererCommand::s_rendererAPI = new OpenGLRendererAPI;
}