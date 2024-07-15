#include <smpch.h>
#include "OpenglFrameBuffer.h"

#include <glad\glad.h>

using namespace std;

//Constructor
OpenglFrameBuffer::OpenglFrameBuffer(const FrameBufferData& _data)
	:data(_data)
{
	Recreate(data.colorBufferIds.size(), data.depthBufferIds.size(), data.stencilBufferIds.size());
}

void OpenglFrameBuffer::Destroy()
{
	DestroyAllStencilBuffers();
	DestroyAllDepthBuffers();
	DestroyAllColorBuffers();

	glDeleteFramebuffers(1, &id);
}

void OpenglFrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	//glViewport(0, 0, data.width, data.height);
}

void OpenglFrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenglFrameBuffer::Recreate(unsigned int colorBufferCount, unsigned int depthBufferCount, unsigned int stencilBufferCount)
{
	DestroyAllStencilBuffers();
	DestroyAllDepthBuffers();
	DestroyAllColorBuffers();

	//if(id == 0)
	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	CreateColorBuffer(colorBufferCount);
	CreateDepthBuffer(depthBufferCount);
	CreateStencilBuffer(stencilBufferCount);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		Logger::LogErrorAlways("Frame Buffer Opengl", "Frame Buffer is incomplete");
}

//resizes the frame buffer
void OpenglFrameBuffer::Resize(unsigned int width, unsigned int height)
{
	data.width = width; data.height = height;
	Recreate(data.colorBufferIds.size(), data.depthBufferIds.size(), data.stencilBufferIds.size());
}

void OpenglFrameBuffer::CreateColorBuffer(unsigned int count)
{
	if (count == 0)
		return;

	for (unsigned int i = 0; i < count; i++)
	{
		data.colorBufferIds.emplace_back(0);
		const unsigned int pos = data.colorBufferIds.size() - 1;

		glGenTextures(1, &data.colorBufferIds[pos]);
		glBindTexture(GL_TEXTURE_2D, data.colorBufferIds[pos]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + pos, GL_TEXTURE_2D, data.colorBufferIds[pos], 0);
	}
}

void OpenglFrameBuffer::CreateDepthBuffer(unsigned int count)
{
	if (count == 0)
		return;

	for (unsigned int i = 0; i < count; i++)
	{
		data.depthBufferIds.emplace_back(0);
		const unsigned int pos = data.depthBufferIds.size() - 1;

		glGenTextures(1, &data.depthBufferIds[pos]);
		glBindTexture(GL_TEXTURE_2D, data.depthBufferIds[pos]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, data.width, data.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, data.depthBufferIds[pos], 0);
	}
}

void OpenglFrameBuffer::CreateStencilBuffer(unsigned int count)
{
	if (count == 0)
		return;
}

void OpenglFrameBuffer::DestroyColorBuffer(unsigned int count)
{
	if (count == 0)
		return;

	for (unsigned int i = 0; i < count; i++)
	{
		glDeleteTextures(1, &data.colorBufferIds[i]);
	}

	vector<unsigned int>::iterator it;
	it = data.colorBufferIds.begin() + count;
	data.colorBufferIds.erase(data.colorBufferIds.begin(), it);
}

void OpenglFrameBuffer::DestroyDepthBuffer(unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{
		glDeleteTextures(1, &data.depthBufferIds[i]);
	}

	vector<unsigned int>::iterator it;
	it = data.depthBufferIds.begin() + count;
	data.depthBufferIds.erase(data.depthBufferIds.begin(), it);
}

void OpenglFrameBuffer::DestroyStencilBuffer(unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{
		glDeleteTextures(1, &data.stencilBufferIds[i]);
	}

	vector<unsigned int>::iterator it;
	it = data.stencilBufferIds.begin() + count;
	data.stencilBufferIds.erase(data.stencilBufferIds.begin(), it);
}

void OpenglFrameBuffer::DestroyAllColorBuffers()
{
	for (unsigned int i = 0; i < data.colorBufferIds.size(); i++)
	{
		glDeleteTextures(1, &data.colorBufferIds[i]);
	}

	data.colorBufferIds.clear();
}

void OpenglFrameBuffer::DestroyAllDepthBuffers()
{
	for (unsigned int i = 0; i < data.depthBufferIds.size(); i++)
	{
		glDeleteTextures(1, &data.depthBufferIds[i]);
	}

	data.depthBufferIds.clear();
}

void OpenglFrameBuffer::DestroyAllStencilBuffers()
{
	for (unsigned int i = 0; i < data.stencilBufferIds.size(); i++)
	{
		glDeleteTextures(1, &data.stencilBufferIds[i]);
	}

	data.stencilBufferIds.clear();
}

unsigned int OpenglFrameBuffer::GetColorBufferId() const
{
	if (data.colorBufferIds.size() < 1)
	{
		Logger::LogErrorAlways("Frame Buffer Opengl", "No Color Buffers are attachted");
		return (unsigned int)0;
	}

	return data.colorBufferIds[0];
}

unsigned int OpenglFrameBuffer::GetDepthBufferId() const
{
	if (data.depthBufferIds.size() < 1)
	{
		Logger::LogErrorAlways("Frame Buffer Opengl", "No Depth Buffers are attachted");
		return (unsigned int)0;
	}

	return data.depthBufferIds[0];
}

unsigned int OpenglFrameBuffer::GetStencilBufferId() const
{
	if (data.stencilBufferIds.size() < 1)
	{
		Logger::LogErrorAlways("Frame Buffer Opengl", "No Stencil Buffers are attachted");
		return (unsigned int)0;
	}

	return data.stencilBufferIds[0];
}

vector<unsigned int>& OpenglFrameBuffer::GetAllColorBufferIds()
{
	return data.colorBufferIds;
}

vector<unsigned int>& OpenglFrameBuffer::GetAllDepthBufferIds()
{
	return data.depthBufferIds;
}

vector<unsigned int>& OpenglFrameBuffer::GetAllStencilBufferIds()
{
	return data.stencilBufferIds;
}