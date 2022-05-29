#include "vrpch.h"
#include "shader.h"
#include <glad/glad.h>
#include "Variant/core/core.h"
#include "Variant/core/log.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

namespace Variant {

	GLenum stringToGlType(std::string type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment" || "pixel")
			return GL_FRAGMENT_SHADER;
		else
			return 0;
	}

	shader::shader(std::string filepath)
		:m_rendererId(0)
	{
		std::string result;
		std::ifstream file(filepath.c_str(), std::ios::in);
		file.seekg(0, std::ios::end);
		result.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&result[0], result.size());

		int typePos = result.find("#type");
		int tokenSize = strlen("#type");

		while (typePos != std::string::npos)
		{
			int eol = result.find_first_of("\n\r",typePos);
			GLenum type = stringToGlType(result.substr(typePos + tokenSize + 1, eol - (typePos + tokenSize + 1)));
			int nextLineStart = eol != std::string::npos ? eol + 1 : std::string::npos;
			typePos = result.find("#type", nextLineStart);
		 	m_shaders[type] = result.substr(nextLineStart, typePos != std::string::npos ? typePos - nextLineStart : result.size()-1);
		}
		compile(m_shaders[GL_VERTEX_SHADER], m_shaders[GL_FRAGMENT_SHADER]);
	}

	void shader::compile(std::string& vertexSrc, std::string& fragmentSrc)
	{
			// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			VR_core_error("shader compilation failed!!");
			std::cout << infoLog.data();
			VR_ASSERT(false);

			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_rendererId = glCreateProgram();
		unsigned int program = m_rendererId;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			VR_core_error("shader compilation failed!!");
			VR_ASSERT(false);

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	
	}
	
	shader::shader(std::string& vertexSrc, std::string& fragmentSrc)
		:m_rendererId(0)
	{
		compile(vertexSrc, fragmentSrc);
	}

	shader::~shader()
	{
		glDeleteProgram(m_rendererId);
	}

	void shader::Bind()
	{
		glUseProgram(m_rendererId);
	}

	void shader::UnBind()
	{
		glUseProgram(0);
	}

	void shader::uploadUniformMat4(std::string uniformName,const glm::mat4& matrix)
	{
		int uniformId = glGetUniformLocation(m_rendererId, uniformName.c_str());
		glUniformMatrix4fv(uniformId, 1, false, glm::value_ptr(matrix));
	}

	void shader::uploadUniformInt(std::string uniformName, int num)
	{
		int uniformId = glGetUniformLocation(m_rendererId, uniformName.c_str());
		glUniform1i(uniformId,num);
	}
	void shader::uploadUniformVec4(std::string uniformName, glm::vec4 vec)
	{
		int uniformId = glGetUniformLocation(m_rendererId, uniformName.c_str());
		glUniform4f(uniformId, vec.r, vec.g, vec.b, vec.a);
	}

}
