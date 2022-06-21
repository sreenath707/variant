#include "vrpch.h"
#include "OpenGLFrameBuffer.h"
#include <glad/glad.h>
#include "Variant/core/core.h"

namespace Variant {
	OpenGLFrameBuffer::OpenGLFrameBuffer(int width, int height)
		:m_width(width),m_height(height)
	{
		glGenFramebuffers(1, &m_rendererId);

		Bind();

		glGenTextures(1, &m_colorBuffer);
		glBindTexture(GL_TEXTURE_2D, m_colorBuffer);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorBuffer, 0);

		VR_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "frame buffer is in complete");
		
	}
	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
	}
	void OpenGLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	unsigned int OpenGLFrameBuffer::getColorBufferId()
	{
		return m_colorBuffer;
	}
}