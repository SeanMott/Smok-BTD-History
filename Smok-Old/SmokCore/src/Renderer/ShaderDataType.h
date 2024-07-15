//defines the engine shader data types

#ifndef ShaderDataType_h
#define ShaderDataType_h

#include <memory>

#include "../Glad/include/glad/glad.h"

enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

//gets the size of a data type
uint32_t ShaderTypeSize(ShaderDataType type);

//gets the count of a data type || float3 = 3
uint32_t GetComponentCount(ShaderDataType type);

//converts engine shader type to glenum (Opengl)
GLenum ConvertShaderTypeToOpengl(ShaderDataType type);
//converts engine shader type to DirectX
//converts engine shader type to Vulkin
//converts engine shader type to Metal

#endif