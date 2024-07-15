#include <smpch.h>
#include "OpenglShader.h"

using namespace std;

//Constructor || vertex and fragment
OpenglShader::OpenglShader(const string& vertexFilePath, const string& fragmentFilePath)
{
	//compile source code
	id = glCreateProgram();
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, Shader::GetSource(vertexFilePath));
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, Shader::GetSource(fragmentFilePath));

	//link vertex and fragment into program
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glValidateProgram(id);

	//clean up
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(id);
}

//Constructor || geometry
//OpenglShader::OpenglShader(const string& geometryFilePath);
//Constructor || compute
//OpenglShader::OpenglShader(const string& computeFilePath);

//gets the uniform location
int OpenglShader::GetLocation(const string& name)
{
	//if stored
	for (auto uniform : uniforms)
	{
		if (uniform.first == name)
			return uniform.second;
	}

	//find
	int location = glGetUniformLocation(id, name.c_str());
	uniforms[name] = location;
	return location;
}

//compiles a shader of any type || for now errors only support vertex and fragment
unsigned int OpenglShader::CompileShader(unsigned int type, const string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		string sType = (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment");
		Logger::LogErrorAlways("Shader", "Failed to compile " + sType + "Shader\n" + (string)message);

		glDeleteShader(id);
		return 0;
	}

	return id;
}