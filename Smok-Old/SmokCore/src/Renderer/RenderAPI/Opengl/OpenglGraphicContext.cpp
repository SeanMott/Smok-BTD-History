#include <smpch.h>
#include "OpenglGraphicContext.h"

#include <glad\glad.h>

bool OpenglGraphicContext::Init(void* _window)
{
	window = (GLFWwindow*)_window;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef Mac_Build
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // MacBuild

	//init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::LogErrorAlways("Opengl API", "Failed to initialize GLAD.");
		return false;
	}

	return true;
}

void OpenglGraphicContext::Destroy()
{
}

void OpenglGraphicContext::Resize(unsigned int xPos, unsigned int yPos, unsigned int width, unsigned int height)
{
	glViewport(xPos, yPos, width, height);
}

void OpenglGraphicContext::VertexBufferDrawCall(unsigned int startingIndex, unsigned int vertexCount)
{
	glDrawArrays(GL_TRIANGLES, startingIndex, vertexCount);
}

void OpenglGraphicContext::IndexBufferDrawCall(unsigned int startingIndex, unsigned int indexCount)
{
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (const void*)startingIndex);
}

void OpenglGraphicContext::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void OpenglGraphicContext::SetClearColor(glm::vec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenglGraphicContext::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenglGraphicContext::SwapRenderBuffer()
{
	glfwSwapBuffers(window);
}

void OpenglGraphicContext::EnableBlending(bool enable)
{
	if (enable)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
		glDisable(GL_BLEND);
}

void OpenglGraphicContext::EnableFaceCulling(bool enable)
{
	if (enable)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void OpenglGraphicContext::EnableZBuffer(bool enable)
{
	if (enable)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}