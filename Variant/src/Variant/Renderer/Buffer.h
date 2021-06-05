#pragma once

namespace Variant {
	class vertexBuffer
	{
	public:
		static vertexBuffer* Create(void* vertices, unsigned int size);

		virtual void Bind() = 0;
		virtual void unbind() = 0;
	};

	class indexBuffer
	{
	public:

		static indexBuffer* Create(void* indices, unsigned int size);

		virtual void Bind() = 0;
		virtual void unbind() = 0;
	};
}