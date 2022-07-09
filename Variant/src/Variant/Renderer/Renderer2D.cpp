#include "vrpch.h"
#include "Renderer2D.h"
#include "vertexArray.h"
#include "shader.h"
#include "RendererCommand.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Variant {

    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCords;
        glm::vec4 color;
    };

	struct RendererData {
		std::shared_ptr<vertexBuffer> vertexBuffer;
		std::shared_ptr<indexBuffer> indexBuffer;
		std::shared_ptr<vertexArray> vertexArray;
		std::shared_ptr<shader> s_shader;
		std::shared_ptr<Texture> whiteTexture;
        //............................
        
        Vertex* BatchVertices = NULL;
        unsigned int numberOfquards = 0;
        
        //......................
        unsigned int maxQuards = 10000;
        unsigned int maxVertices = 4*maxQuards;
        unsigned int maxIndices = 6* maxQuards;
        
	};

    

	RendererData* s_rendererData = new RendererData();
	

	void Renderer2D::Init()
	{
		
		s_rendererData->vertexArray.reset(Variant::vertexArray::Create());

//		float vertices[4 * 5] =
//		{
//			0.5f,0.5f,0.0f,   0.0,0.0,
//			-0.5f,0.5f,0.0f,  1.0,0.0,
//			-0.5f,-0.5f,0.0f, 1.0,1.0,
//			 0.5f,-0.5f,0.0f, 0.0,1.0,
//		};

		s_rendererData->vertexBuffer.reset(vertexBuffer::Create(sizeof(Vertex) * s_rendererData->maxVertices));
        s_rendererData->BatchVertices = new Vertex[s_rendererData->maxVertices];
		s_rendererData->vertexBuffer->Bind();

		BufferLayout layout = {
			{shaderDataType::Float3,"position"},
			{shaderDataType::Float2,"textCoords"},
            {shaderDataType::Float4,"color"}
		};

		s_rendererData->vertexBuffer->setLayout(layout);
		s_rendererData->vertexArray->addVertexBuffer(s_rendererData->vertexBuffer);


//		unsigned int indices[6] = { 0,1,2,2,3,0 };
        unsigned int* indices = new unsigned int[6*s_rendererData->maxIndices];
        int offset = 0;
        for(int i=0;i<s_rendererData->maxIndices;i+=6){
            indices[i+ 0] = offset+0;
            indices[i+ 1] = offset+1;
            indices[i+ 2] = offset+2;
            indices[i+ 3] = offset+2;
            indices[i+ 4] = offset+3;
            indices[i+ 5] = offset+0;
            offset+=4;
        }
		s_rendererData->indexBuffer.reset(indexBuffer::Create(indices, s_rendererData->maxQuards));
		s_rendererData->indexBuffer->Bind();
		s_rendererData->vertexArray->SetIndexBuffer(s_rendererData->indexBuffer);

		s_rendererData->s_shader.reset(new shader("/Users/sreenath707/Developer/projects/variant/SandBox/Assets/Shaders/shader.glsl"));

		s_rendererData->whiteTexture.reset(new Texture(glm::vec4(1.0)));

	}
	void Renderer2D::ShutDown()
	{
		delete s_rendererData;
	}
	void Renderer2D::BeginScene(OrthographicCamera camera)
	{
		s_rendererData->s_shader->Bind();
		s_rendererData->s_shader->uploadUniformMat4("u_viewProjection", camera.getProjectionView());
	}
	void Renderer2D::EndScene()
	{
        s_rendererData->vertexBuffer->uploadData((void*)s_rendererData->BatchVertices,
                                                 s_rendererData->numberOfquards*4*sizeof(Vertex));
        RendererCommand::drawIndexed(s_rendererData->vertexArray, 6*s_rendererData->numberOfquards);
        
	}
	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec2 size,float rotation, glm::vec4 color)
	{
		s_rendererData->vertexArray->Bind();
		s_rendererData->whiteTexture->Bind();
        //        {
        //            0.5f,0.5f,0.0f,   0.0,0.0,
        //            -0.5f,0.5f,0.0f,  1.0,0.0,
        //            -0.5f,-0.5f,0.0f, 1.0,1.0,
        //             0.5f,-0.5f,0.0f, 0.0,1.0,
        //        };
            s_rendererData->BatchVertices[s_rendererData->numberOfquards*4 +0] = {
                {size.x*0.5+position.x, size.y*0.5+position.y,position.z},
                {0,0},
                color
            };
            s_rendererData->BatchVertices[s_rendererData->numberOfquards*4 +1] ={
                {size.x*-0.5+position.x, size.y*0.5+position.y,position.z},
                {1,0},
                color
            };
            s_rendererData->BatchVertices[s_rendererData->numberOfquards*4 +2] ={
                {size.x*-0.5+position.x,size.y*-0.5+position.y,position.z},
                {1,1},
                color
            };
            s_rendererData->BatchVertices[s_rendererData->numberOfquards*4 +3] ={
                {size.x*0.5+position.x ,size.y*-0.5+position.y,position.z},
                {0,1},
                color
            };
            s_rendererData->numberOfquards++;
//		glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0), position)
//			* glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0.0f,0.0f,1.0f))
//			* glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
//		s_rendererData->s_shader->uploadUniformMat4("u_transform", transformMatrix);
//		s_rendererData->s_shader->uploadUniformInt("u_texture", 0);
//		s_rendererData->s_shader->uploadUniformVec4("u_color", color);

		//RendererCommand::drawIndexed(s_rendererData->vertexArray);
	}
	void Renderer2D::DrawTexture(glm::vec3 position, glm::vec2 size, float rotation, std::shared_ptr<Texture> texture)
	{
		s_rendererData->vertexArray->Bind();
		texture->Bind();

		glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0), position)
			* glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0), glm::vec3(size, 1.0));
		s_rendererData->s_shader->uploadUniformMat4("u_transform", transformMatrix);
		s_rendererData->s_shader->uploadUniformInt("u_texture", 0);
		s_rendererData->s_shader->uploadUniformVec4("u_color", {1,1,1,1});

		RendererCommand::drawIndexed(s_rendererData->vertexArray);
	}
}
