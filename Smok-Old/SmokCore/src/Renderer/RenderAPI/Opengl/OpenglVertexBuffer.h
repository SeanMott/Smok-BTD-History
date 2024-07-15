//the Opengl implementation of the vertex buffer

#ifndef OpenglVertexBuffer_h
#define OpenglVertexBuffer_h

#include <Renderer\VertexBuffer.h>

#include <glad\glad.h>

class OpenglVertexBuffer : public VertexBuffer
{
	//vars
private:

	unsigned int vertexArray, vertexBuffer, size;

	BufferLayout layout;

	//methods
public:

	//Constructor
	OpenglVertexBuffer(float* vertices, unsigned int _size);
	//Deconstructor
	virtual ~OpenglVertexBuffer() { Destroy(); }

	//binds the buffer
	inline void Bind() const override { glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); }
	//unbinds the buffer
	inline void Unbind() const override { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	//destroys the buffer
	inline void Destroy() override { glDeleteBuffers(1, &vertexBuffer); }

	//sets the layout
	void SetLayout(const BufferLayout& _layout) override;
	//returns the layout
	inline const BufferLayout& GetLayout() const override { return layout; }

	//gets the size
	inline unsigned int GetSize() override { return size; }
};

#endif