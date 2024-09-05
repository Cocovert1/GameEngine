#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>

namespace Bengine {

	GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0) {

	}

	GLSLProgram::~GLSLProgram() {

	}

	// read path, and use OpenGL to compile them
	void GLSLProgram::compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		_programID = glCreateProgram();

		//create vertex shader object and store id
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0) {
			fatalError("Vertex shader failed to be created");
		}

		//create fragment shader object and store id
		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0) {
			fatalError("Fragment shader failed to be created");
		}

		//compile our shaders
		compileShader(vertexShaderPath, _vertexShaderID);
		compileShader(fragmentShaderPath, _fragmentShaderID);
	}

	void GLSLProgram::linkShaders() {
		// Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		// Link our program
		glLinkProgram(_programID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(_programID);
			// Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			// Use the infoLog as you see fit.
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader failed to link");
		}

		// Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	//adds an attribute to our shader. Call between compiling and linking
	void GLSLProgram::addAttribute(const std::string& attributeName) {
		//postfix addition, we are binding our vertex shader input attribute
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}

	//will turn text shader into shader object and compile
	void GLSLProgram::compileShader(const std::string& filePath, GLuint id) {
		//open ifstream to read vertex shader 
		std::ifstream vertexFile(filePath);
		if (vertexFile.fail()) {
			perror(filePath.c_str());
			fatalError("Failed to open " + filePath);
		}

		//store content of file in fileContents
		std::string fileContents = "";
		std::string line;
		while (std::getline(vertexFile, line)) {
			fileContents += line + "\n";
		}
		vertexFile.close();

		//make a ptr to our string of contents for parameter
		const char* contentsPtr = fileContents.c_str();
		//give actual text string representing the GLSL source code
		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//Provide the infolog in whatever manor you deem best
			//Exit with failure
			glDeleteShader(id); //Don't leak the shader

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader " + filePath + " failed to compile");
		}
	}

	GLint GLSLProgram::getUniformLocaiton(const std::string& uniformName) {
		GLint location = glGetUniformLocation(_programID, uniformName.c_str()); //this will find the index of the uniform we created in shader
		if (location == GL_INVALID_INDEX) {
			fatalError("Uniform" + uniformName + " not found in shader");
		}

		return location;
	}

	void GLSLProgram::use() {
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++) {
			glEnableVertexAttribArray(i); //we need to enable the attribute or else it won't be used
		}
	}
	void GLSLProgram::unuse() {
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}
}