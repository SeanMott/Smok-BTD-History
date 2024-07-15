#include <smpch.h>
#include "ShaderDataType.h"

//gets the size of a data type
uint32_t ShaderTypeSize(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::None:
		return 0;
	case ShaderDataType::Float:
		return 4;
	case ShaderDataType::Float2:
		return 8;
	case ShaderDataType::Float3:
		return 12;
	case ShaderDataType::Float4:
		return 16;
	case ShaderDataType::Mat3:
		return 36;
	case ShaderDataType::Mat4:
		return 64;
	case ShaderDataType::Int:
		return 4;
	case ShaderDataType::Int2:
		return 8;
	case ShaderDataType::Int3:
		return 12;
	case ShaderDataType::Int4:
		return 16;
	case ShaderDataType::Bool:
		return 1;
	}

	printf("Unknown shader data type.\n");
	return 0;
}

//gets the count of a data type || float3 = 3
uint32_t GetComponentCount(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::None:
		return 0;
	case ShaderDataType::Float:
		return 1;
	case ShaderDataType::Float2:
		return 2;
	case ShaderDataType::Float3:
		return 3;
	case ShaderDataType::Float4:
		return 4;
	case ShaderDataType::Mat3:
		return 9;
	case ShaderDataType::Mat4:
		return 16;
	case ShaderDataType::Int:
		return 1;
	case ShaderDataType::Int2:
		return 2;
	case ShaderDataType::Int3:
		return 3;
	case ShaderDataType::Int4:
		return 4;
	case ShaderDataType::Bool:
		return 1;
	default:
		printf("Unknown shader data type.\n");
		return 0;
	}
}

//converts engine shader type to glenum (Opengl)
GLenum ConvertShaderTypeToOpengl(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:
		return GL_FLOAT;
	case ShaderDataType::Float2:
		return GL_FLOAT;
	case ShaderDataType::Float3:
		return GL_FLOAT;
	case ShaderDataType::Float4:
		return GL_FLOAT;
	case ShaderDataType::Mat3:
		return GL_FLOAT;
	case ShaderDataType::Mat4:
		return GL_FLOAT;
	case ShaderDataType::Int:
		return GL_INT;
	case ShaderDataType::Int2:
		return GL_INT;
	case ShaderDataType::Int3:
		return GL_INT;
	case ShaderDataType::Int4:
		return GL_INT;
	case ShaderDataType::Bool:
		return GL_BOOL;
	}

	printf("Unknown shader data type.\n");
	return 0;
}