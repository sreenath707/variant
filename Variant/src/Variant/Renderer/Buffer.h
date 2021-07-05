#pragma once
#include<string>
#include<Variant/core/core.h>
#include<Variant/core/log.h>

namespace Variant {

	enum class shaderDataType
	{
		None=0,Float,Float2,Float3,Float4,Int,Int2,Int3,Int4,Mat3,Mat4,Bool
	};

	static unsigned int getShaderDataTypeSize(shaderDataType type)
	{
		switch (type)
		{
		case Variant::shaderDataType::None: VR_core_error("none is not a type");
			return 0;
			break;
		case Variant::shaderDataType::Float: return sizeof(float);
			break;
		case Variant::shaderDataType::Float2: return sizeof(float)*2;
			break;
		case Variant::shaderDataType::Float3: return sizeof(float)*3;
			break;
		case Variant::shaderDataType::Float4: return sizeof(float)*4;
			break;
		case Variant::shaderDataType::Int: return sizeof(int);
			break;
		case Variant::shaderDataType::Int2: return sizeof(float)*2;
			break;
		case Variant::shaderDataType::Int3: return sizeof(float)*3;
			break;
		case Variant::shaderDataType::Int4: return sizeof(float)*4;
			break;
		case Variant::shaderDataType::Mat3: return sizeof(int)*3*3;
			break; 
		case Variant::shaderDataType::Mat4: return sizeof(float) * 4 * 4;
			break;
		case Variant::shaderDataType::Bool: return sizeof(bool);
			break;
		default: return 0;
		}
	}

	class layoutElement
	{
	public:
		std::string name;
		unsigned int size;
		unsigned int offset;
		bool normalized;
		shaderDataType shaderType;

	public:
		layoutElement(shaderDataType type,std::string name)
			:name(name),size(getShaderDataTypeSize(type)),normalized(false),offset(0),shaderType(type){}
					

	};



	class BufferLayout
	{
	private:
		unsigned int m_stride;

	public:
		std::vector<layoutElement> m_Elements;

		BufferLayout() = default;

		BufferLayout(std::initializer_list<layoutElement> elements)
			:m_Elements(elements)
		{
			
			m_stride = 0;
			unsigned int offset = 0;
			for (auto& element : m_Elements)
			{
				element.offset = offset;
				offset += element.size;
				m_stride += element.size;
			}
			

		}

		std::vector<layoutElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<layoutElement>::iterator end() { return m_Elements.end(); }

		unsigned int getStride() { return m_stride; }
		const std::vector<layoutElement>& getLayout()const{ return m_Elements; }


	};
	

	
	class vertexBuffer
	{
	private:
		BufferLayout m_layout;
	public:
		static vertexBuffer* Create(void* vertices, unsigned int size);

		virtual void Bind() = 0;
		virtual void unbind() = 0;
		vertexBuffer() = default;

		void setLayout(BufferLayout layout) { m_layout = layout; }
		BufferLayout& getLayout(){ return  m_layout; }

	};

	class indexBuffer
	{
	public:

		static indexBuffer* Create(void* indices, unsigned int count);

		virtual void Bind() = 0;
		virtual void unbind() = 0;
		virtual unsigned int getCount() = 0;
	};
}