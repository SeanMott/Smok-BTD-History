#include <smpch.h>
#include "VertexBuffer.h"

#include <Renderer\RenderAPI\RenderAPI.h>
#include <Renderer\RenderAPI\Opengl\OpenglVertexBuffer.h>
//#include <Renderer\RenderAPI\DirectX\DirectXVertexBuffer.h>
//#include <Renderer\RenderAPI\Vulkin\VulkinVertexBuffer.h>
//#include <Renderer\RenderAPI\Metal\MetalVertexBuffer.h>

//creates a vertex buffer
VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int _size)
{
	RenderAPIType type = RenderAPI::GetAPI();

	if (type == RenderAPIType::Vulkin)
	{
		Logger::LogErrorAlways("Vertex Buffer", "Vulkin is currently not supported, Opengl will be used.");
		//return new VulkinVertexBuffer(vertices, _size);
		return new OpenglVertexBuffer(vertices, _size);
	}

	else if (type == RenderAPIType::DirectX)
	{
		Logger::LogErrorAlways("Vertex Buffer", "DirectX is currently not supported, Opengl will be used.");
		//return new DirectXVertexBuffer(vertices, _size);
		return new OpenglVertexBuffer(vertices, _size);
	}

	else if (type == RenderAPIType::Metal)
	{
		Logger::LogErrorAlways("Vertex Buffer", "Metal is currently not supported, Opengl will be used.");
		//return new MetalVertexBuffer(vertices, _size);
		return new OpenglVertexBuffer(vertices, _size);
	}

	else
		return new OpenglVertexBuffer(vertices, _size);
}