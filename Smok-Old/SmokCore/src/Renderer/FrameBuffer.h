//base Frame Buffer

#ifndef FrameBuffer_h
#define FrameBuffer_h

#include <vector>

//defines data for the Frame Buffer
struct FrameBufferData
{
	unsigned int width, height;
	//formate
	unsigned int samples = 1;

	bool useSwapChain = false; //false = unbind || true = bind

	std::vector<unsigned int> colorBufferIds, depthBufferIds, stencilBufferIds; //, depthSencilBufferIds;
};

class FrameBuffer
{
	//methods
public:

	virtual ~FrameBuffer() {}

	//creates a frame buffer
	static FrameBuffer* Create(const FrameBufferData& data);

	//destroys a frame buffer
	virtual void Destroy() = 0;

	//returns the frame buffer data
	virtual const FrameBufferData& GetData() const = 0;

	//binds buffer
	virtual void Bind() = 0;
	//unbinds buffer
	virtual void Unbind() = 0;

	//recreates the frame buffer
	virtual void Recreate(unsigned int colorBufferCount = 0, unsigned int depthBufferCount = 0, unsigned int stencilBufferCount = 0) = 0;

	//resizes the frame buffer
	virtual void Resize(unsigned int width, unsigned int height) = 0;

	//adds a color buffer
	virtual void CreateColorBuffer(unsigned int count = 0) = 0;
	//adds a depth buffer
	virtual void CreateDepthBuffer(unsigned int count = 0) = 0;
	//adds a stencil buffer
	virtual void CreateStencilBuffer(unsigned int count = 0) = 0;

	//destroys a color buffer || starts at the 0 element
	virtual void DestroyColorBuffer(unsigned int count = 1) = 0;
	//destroys a depth buffer || starts at the 0 element
	virtual void DestroyDepthBuffer(unsigned int count = 1) = 0;
	//destroys a stencil buffer || starts at the 0 element
	virtual void DestroyStencilBuffer(unsigned int count = 1) = 0;

	//destroys all color buffers
	virtual void DestroyAllColorBuffers() = 0;
	//destroys all depth buffers
	virtual void DestroyAllDepthBuffers() = 0;
	//destroys a;; stencil buffer
	virtual void DestroyAllStencilBuffers() = 0;

	//gets the first color buffer id
	virtual unsigned int GetColorBufferId() const = 0;
	//gets the first depth buffer id
	virtual unsigned int GetDepthBufferId() const = 0;
	//gets the first stencil buffer id
	virtual unsigned int GetStencilBufferId() const = 0;

	//gets all the color buffer ids
	virtual std::vector<unsigned int>& GetAllColorBufferIds() = 0;
	//gets all the depth buffer ids
	virtual std::vector<unsigned int>& GetAllDepthBufferIds() = 0;
	//gets all the stencil buffer ids
	virtual std::vector<unsigned int>& GetAllStencilBufferIds() = 0;

};

#endif