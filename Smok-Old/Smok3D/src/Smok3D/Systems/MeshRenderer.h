//defines a mesh renderer system

#ifndef MeshRenderer_h
#define MeshRenderer_h

#include <Renderer\IndexBuffer.h>
#include <Renderer\VertexBuffer.h>
#include <Renderer\Assets\Shader.h>
#include <Renderer\Assets\Texture.h>

class MeshRenderer
{
	//vars
private:

	Shader* lastShader = nullptr;
	Texture* lastTexture = nullptr;
	VertexBuffer* lastVertexBuffer = nullptr;
	IndexBuffer* lastIndexBuffer = nullptr;

	//methods
public:

	//renders the meshs
	void RenderMesh();

};

#endif