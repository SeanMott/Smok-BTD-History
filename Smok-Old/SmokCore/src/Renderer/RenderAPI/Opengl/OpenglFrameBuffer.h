//Opengl implementation of the frame buffer

#ifndef OpenglFrameBuffer_h
#define OpenglFrameBuffer_h

#include <Renderer\FrameBuffer.h>

class OpenglFrameBuffer : public FrameBuffer
{
	//vars
private:

	FrameBufferData data;

	unsigned int id;

	//methods
public:

	//Constructor
	OpenglFrameBuffer(const FrameBufferData& _data);
	//Deconstructor
	virtual ~OpenglFrameBuffer() { Destroy(); }

	// Inherited via FrameBuffer
	void Destroy() override;
	void Bind() override;
	void Unbind() override;
	//recreates the frame buffer
	void Recreate(unsigned int colorBufferCount = 0, unsigned int depthBufferCount = 0, unsigned int stencilBufferCount = 0) override;

	//resizes the frame buffer
	void Resize(unsigned int width, unsigned int height) override;

	// Inherited via FrameBuffer
	void CreateColorBuffer(unsigned int count = 0) override;
	void CreateDepthBuffer(unsigned int count = 0) override;
	void CreateStencilBuffer(unsigned int count = 0) override;
	unsigned int GetColorBufferId() const override;
	unsigned int GetDepthBufferId() const override;
	unsigned int GetStencilBufferId() const override;
	std::vector<unsigned int>& GetAllColorBufferIds() override;
	std::vector<unsigned int>& GetAllDepthBufferIds() override;
	std::vector<unsigned int>& GetAllStencilBufferIds() override;
	void DestroyColorBuffer(unsigned int count = 1) override;
	void DestroyDepthBuffer(unsigned int count = 1) override;
	void DestroyStencilBuffer(unsigned int count = 1) override;
	void DestroyAllColorBuffers() override;
	void DestroyAllDepthBuffers() override;
	void DestroyAllStencilBuffers() override;

	inline const FrameBufferData& GetData() const override { return data; }
};

#endif