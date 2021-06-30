#include "vrpch.h"
#include "vertexArray.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace Variant {
	
	 vertexArray* vertexArray::Create()
	{
		 return new OpenGLVertexArray;
	}
}