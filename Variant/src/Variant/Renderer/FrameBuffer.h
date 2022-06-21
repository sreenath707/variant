#pragma once


namespace Variant {
	class FrameBuffer
	{
	private:
		
	public:
		static FrameBuffer* Create(float width, float height);
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual unsigned int getColorBufferId() = 0;
		virtual void reValidate(float width, float height) = 0;
	};
}