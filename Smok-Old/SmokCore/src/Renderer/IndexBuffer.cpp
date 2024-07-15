#include <smpch.h>
#include "IndexBuffer.h"

#include <Renderer\RenderAPI\RenderAPI.h>
#include <Renderer\RenderAPI\Opengl\OpenglIndexBuffer.h>
//#include <Renderer\RenderAPI\DirectX\DirectXIndexBuffer.h>
//#include <Renderer\RenderAPI\Vulkin\VulkinIndexBuffer.h>
//#include <Renderer\RenderAPI\Metal\MetalIndexBuffer.h>

//creates a Index buffer
IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int _count)
{
	RenderAPIType type = RenderAPI::GetAPI();

	if (type == RenderAPIType::Vulkin)
	{
		Logger::LogErrorAlways("Index Buffer", "Vulkin is currently not supported, Opengl will be used.");
		//return new VulkinIndexBuffer(indices, _count);
		return new OpenglIndexBuffer(indices, _count);
	}

	else if (type == RenderAPIType::DirectX)
	{
		Logger::LogErrorAlways("Index Buffer", "DirectX is currently not supported, Opengl will be used.");
		//return new DirectXIndexBuffer(indices, _count);
		return new OpenglIndexBuffer(indices, _count);
	}

	else if (type == RenderAPIType::Metal)
	{
		Logger::LogErrorAlways("Index Buffer", "Metal is currently not supported, Opengl will be used.");
		//return new MetalIndexBuffer(indices, _count);
		return new OpenglIndexBuffer(indices, _count);
	}

	else
		return new OpenglIndexBuffer(indices, _count);
}