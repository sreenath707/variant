#include "vrpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Variant {

	unsigned int shaderTypeToGLType(shaderDataType type)
	{
		switch (type)
		{
		case Variant::shaderDataType::None: VR_core_error("none is not a type");
			return 0;
			break;
		case Variant::shaderDataType::Float: return GL_FLOAT;
			break;
		case Variant::shaderDataType::Float2: return GL_FLOAT;
			break;
		case Variant::shaderDataType::Float3: return GL_FLOAT;
			break;
		case Variant::shaderDataType::Float4: return GL_FLOAT;
			break;
		case Variant::shaderDataType::Int: return GL_INT;
			break;
		case Variant::shaderDataType::Int2: return GL_INT;
			break;
		case Variant::shaderDataType::Int3: return GL_INT;
			break;
		case Variant::shaderDataType::Int4: return GL_INT;
			break;
		case Variant::shaderDataType::Mat3: return GL_INT;
			break;
		case Variant::shaderDataType::Mat4: return GL_INT;
			break;
		case Variant::shaderDataType::Bool: return GL_BOOL;
			break;
		default:
			return 0;
			break;
		}
	}

	unsigned int getBufferCount(shaderDataType type)
	{
		switch (type)
		{
		case Variant::shaderDataType::None: VR_core_error("none is not a type");
			return 0;
			break;
		case Variant::shaderDataType::Float: return 1;
			break;
		case Variant::shaderDataType::Float2: return 2;
			break;
		case Variant::shaderDataType::Float3: return 3;
			break;
		case Variant::shaderDataType::Float4: return 4;
			break;
		case Variant::shaderDataType::Int: return 1;
			break;
		case Variant::shaderDataType::Int2: return 2;
			break;
		case Variant::shaderDataType::Int3: return 3;
			break;
		case Variant::shaderDataType::Int4: return 4;
			break;
		case Variant::shaderDataType::Mat3: return 3 * 3;
			break;
		case Variant::shaderDataType::Mat4: return 4 * 4;
			break;
		case Variant::shaderDataType::Bool: return 1;
			break;
		default:
			return 0;
			break;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_rendererId);
	}

	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<indexBuffer>& Buffer)
	{
		glBindVertexArray(m_rendererId);
		Buffer->Bind();
		m_indexBuffer = Buffer;
	}

	void OpenGLVertexArray::addVertexBuffer(std::shared_ptr<vertexBuffer>& Buffer)
	{
		glBindVertexArray(m_rendererId);
		Buffer->Bind();

		BufferLayout layout = Buffer->getLayout();
		for (auto element : layout)
		{
			glEnableVertexAttribArray(m_vertexBufferIndex);
			glVertexAttribPointer(m_vertexBufferIndex,
				getBufferCount(element.shaderType),
				shaderTypeToGLType(element.shaderType),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.offset);
			
			m_vertexBuffers.push_back(Buffer);
			m_vertexBufferIndex++;
		}
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_rendererId);
	}

	void OpenGLVertexArray::UnBind()
	{
		glBindVertexArray(0);

	}

}
