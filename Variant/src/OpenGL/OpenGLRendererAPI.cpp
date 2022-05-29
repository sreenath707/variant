#include "vrpch.h"
#include "OpenGLRendererAPI.h"
#include "glad/glad.h"


namespace Variant {
	void OpenGLRendererAPI::drawIndexed(std::shared_ptr<vertexArray> v_vertexArray)
	{
		glDrawElements(GL_TRIANGLES, v_vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
	void OpenGLRendererAPI::setColor(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::clearColor()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void OpenGLRendererAPI::setViewPort(float width, float height)
	{
		glViewport(0, 0, width, height);
	}
}