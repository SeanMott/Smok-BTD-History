#include <smpch.h>
#include "OpenglVertexBuffer.h"

//Constructor
OpenglVertexBuffer::OpenglVertexBuffer(float* vertices, unsigned int _size)
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _size, vertices, GL_STATIC_DRAW);
	size = _size;
}

//sets the layout
void OpenglVertexBuffer::SetLayout(const BufferLayout& _layout)
{
	layout = _layout;

	uint32_t count = 0;
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(count);
		glVertexAttribPointer(count, GetComponentCount(element.type), ConvertShaderTypeToOpengl(element.type), element.isNormalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.offset);
		//printf("Vetrex Attrib: Count: %i, ShaderType: %i, Stride: %i, Offset: %i\n", count, element.type, layout.GetStride(), element.offset);
		count++;
	}
}
