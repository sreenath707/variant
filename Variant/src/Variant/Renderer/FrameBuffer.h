#pragma once


namespace Variant {
	class FrameBuffer
	{
	private:
		
	public:
		static FrameBuffer* Create(unsigned int width, unsigned int height);
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual unsigned int getColorBufferId() = 0;
	};
}