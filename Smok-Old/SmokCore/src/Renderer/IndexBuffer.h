//base index buffer

#ifndef IndexBuffer_h
#define IndexBuffer_h

class IndexBuffer
{
public:

	virtual ~IndexBuffer() {}

	//creates a index buffer
	static IndexBuffer* Create(unsigned int* indices, unsigned int _count);

	//destroys a index buffer
	virtual void Destroy() = 0;

	//binds a buffer
	virtual void Bind() const = 0;
	//unbinds a buffer
	virtual void Unbind() const = 0;

	//returns the count
	virtual unsigned int GetCount() const = 0;
};

#endif