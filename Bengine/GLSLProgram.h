#pragma once
#include <string>
#include <GL/glew.h>

namespace Bengine {

	//handles compilation, linking, and usage of GLSL shader program
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		void linkShaders();

		void addAttribute(const std::string& attributeName);

		GLint getUniformLocaiton(const std::string& uniformName);

		void use();
		void unuse();

	private:
		int _numAttributes;

		// id that refers to entire program/finish product
		GLuint _programID;

		// vertex and fragment ID 
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		void compileShader(const std::string& filePath, GLuint id);
	};

}

