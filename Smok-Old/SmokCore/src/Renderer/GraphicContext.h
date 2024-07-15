//base Graphic Context

#ifndef GraphicContext_h
#define GraphicContext_h

#include <glm.hpp>

class GraphicContext
{
public:

	//creates a graphic context
	static GraphicContext* Create();

	virtual ~GraphicContext() {}

	//inits the context
	virtual bool Init(void* _window) = 0;
	//destroys the context
	virtual void Destroy() = 0;

	//resizes the view port
	virtual void Resize(unsigned int xPos, unsigned int yPos, unsigned int width, unsigned int height) = 0;

	//sets the clear color
	virtual void SetClearColor(float r, float g, float b, float a = 1.0f) = 0;
	virtual void SetClearColor(glm::vec4 color) = 0;
	//clears the screen
	virtual void Clear() = 0;

	//makes a vertex buffer draw call
	virtual void VertexBufferDrawCall(unsigned int startingIndex, unsigned int vertexCount) = 0;
	//makes a index buffer draw call
	virtual void IndexBufferDrawCall(unsigned int startingIndex, unsigned int indexCount) = 0;
	//makes a batch draw call

	//swaps the render buffer
	virtual void SwapRenderBuffer() = 0;

	//enables face culling
	virtual void EnableFaceCulling(bool enable = true) = 0;
	//enables blending
	virtual void EnableBlending(bool enable = true) = 0;
	//enables Z buffer
	virtual void EnableZBuffer(bool enable = true) = 0;
};

#endif