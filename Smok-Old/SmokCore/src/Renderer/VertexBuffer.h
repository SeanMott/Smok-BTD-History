//base vertex buffer

#ifndef VertexBuffer_h
#define VertexBuffer_h

#include <Renderer\BufferLayout.h>

class VertexBuffer
{
public:

	virtual ~VertexBuffer() {}

	//creates a vertex buffer
	static VertexBuffer* Create(float* vertices, unsigned int _size);

	//destroys a vertex buffer
	virtual void Destroy() = 0;
	
	//sets the buffer layout
	virtual void SetLayout(const BufferLayout& layout) = 0;
	//gets the layout
	virtual const BufferLayout& GetLayout() const = 0;

	//binds a buffer
	virtual void Bind() const = 0;
	//unbinds a buffer
	virtual void Unbind() const = 0;

	//gets the size
	virtual unsigned int GetSize() = 0;
};

#endif