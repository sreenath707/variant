#include "vrpch.h"
#include "vertexArray.h"
#include "OpenGL/OpenGLVertexArray.h"
#include "RendererAPI.h"


namespace Variant {
	
	 vertexArray* vertexArray::Create()
	{
		 switch (RendererAPI::getAPI())
		 {
		 case RendererAPI::API::None: VR_core_error("None is not supported!");
			 return nullptr;
			 break;
		 case RendererAPI::API::OpenGL: return new OpenGLVertexArray;
			 break;
		 default:
			 return nullptr;
		 }
		 
	}
}