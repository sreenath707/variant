#pragma once
#include "Variant/Renderer/FrameBuffer.h"

namespace Variant {
	class OpenGLFrameBuffer :public FrameBuffer
	{
	private:
		unsigned int m_rendererId;
		unsigned int m_height;
		unsigned int m_width;
		unsigned int m_colorBuffer;
		unsigned int m_deapthBuffer;

	public:
		OpenGLFrameBuffer(float width, float height);
		
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual unsigned int getColorBufferId() override;
		virtual void reValidate(float width, float height) override;
	};
}