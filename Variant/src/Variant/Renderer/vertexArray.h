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
		virtual std::vector<std::shared_ptr<vertexBuffer>>& getVertexBuffers() = 0;
		virtual std::shared_ptr<indexBuffer>& getIndexBuffer() = 0;


		static vertexArray* Create();

	};
}