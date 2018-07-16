#pragma once

#include "glew.h"
#include "freeglut.h"
#include <iostream>
#include <map>


class ShaderLoader
{
	private:

		std::string ReadShader(char *filename);
		GLuint CreateShader(GLenum shaderType,
			std::string source,
			char* shaderName);
		std::map<std::string, std::string> shaderMap;

	public:

		ShaderLoader(void);
		~ShaderLoader(void);
		GLuint CreateProgram(char* VertexShaderFilename,
			char* FragmentShaderFilename);

};
