#include <smpch.h>
#include "OpenglIndexBuffer.h"

//Constructor
OpenglIndexBuffer::OpenglIndexBuffer(unsigned int* indices, unsigned int _count)
	:count(_count)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
}