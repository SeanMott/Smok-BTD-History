//Opengl implementation of the graphic context

#ifndef OpenglGraphicContext_h
#define OpenglGraphicContext_h

#include <Renderer\GraphicContext.h>

#include <GLFW\glfw3.h>

class OpenglGraphicContext : public GraphicContext
{
	//vars
private:

	GLFWwindow* window;

	//methods
public:

	virtual ~OpenglGraphicContext() { Destroy(); }

	// Inherited via GraphicContext
	bool Init(void* _window) override;
	void Destroy() override;
	void Resize(unsigned int xPos, unsigned int yPos, unsigned int width, unsigned int height) override;
	void VertexBufferDrawCall(unsigned int startingIndex, unsigned int vertexCount) override;
	void IndexBufferDrawCall(unsigned int startingIndex, unsigned int indexCount) override;
	void SetClearColor(float r, float g, float b, float a = 1.0f) override;
	void SetClearColor(glm::vec4 color) override;
	void Clear() override;
	void SwapRenderBuffer() override;
	void EnableFaceCulling(bool enable = true) override;
	void EnableBlending(bool enable = true) override;
	void EnableZBuffer(bool enable = true) override;
};

#endif