//defines a mesh component

#ifndef Mesh_h
#define Mesh_h

#include <Renderer\IndexBuffer.h>
#include <Renderer\VertexBuffer.h>
#include <Renderer\Assets\Shader.h>
#include <Renderer\Assets\Texture.h>

struct Mesh
{
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	Texture* texture = nullptr;
	unsigned int textureSlot = 0;
	Shader* shader = nullptr;
	
	bool isActive = true;
};

#endif