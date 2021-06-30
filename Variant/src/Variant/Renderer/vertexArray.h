#pragma once
#include "Buffer.h"
#include <memory.h>

namespace Variant {
	class vertexArray
	{
	public:

		vertexArray(){}

		virtual void addVertexBuffer(std::shared_ptr<vertexBuffer>& Buffer) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<indexBuffer>& Buffer) =0;

		virtual void Bind()=0;
		virtual void UnBind() = 0;

		static vertexArray* Create();

	};
}