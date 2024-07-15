//Opengl implementation of the index buffer

#ifndef OpenglIndexBuffer_h
#define OpenglIndexBuffer_h

#include <Renderer\IndexBuffer.h>

#include <glad\glad.h>

class OpenglIndexBuffer : public IndexBuffer
{
	//vars
private:

	unsigned int id, count;

	//methods
public:

	//Constructor
	OpenglIndexBuffer(unsigned int* indices, unsigned int _count);
	//Deconstructor
	virtual ~OpenglIndexBuffer() { Destroy(); }

	//binds the buffer
	inline void Bind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
	//unbinds the buffer
	inline void Unbind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	//destroys the buffer
	inline void Destroy() override { glDeleteBuffers(1, &id); }

	//returns the count of the buffer
	inline unsigned int GetCount() const override { return count; }
};

#endif