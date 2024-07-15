//define the SpriteRenderer system

#ifndef SpriteRenderer_h
#define SpriteRenderer_h

#include <Renderer\Assets\Shader.h>
#include <Renderer\Assets\Texture.h>
#include <Renderer\VertexBuffer.h>
#include <Renderer\IndexBuffer.h>
#include <Renderer\GraphicContext.h>

class SpriteRenderer
{
	//vars
private:

	static Shader* lastShader;
	static Texture* lastTexture;
	static std::string lastShaderName;
	static std::string lastTextureName;

	static VertexBuffer* spriteBuffer;
	static IndexBuffer* spriteIndexBuffer;

	static bool hasSentWarning;

	static GraphicContext* context;

	//methods
public:

	inline ~SpriteRenderer() { Shutdown(); }

	//sets the sprite renderer and links it
	static void Init();
	//shuts down the sprite renderer
	static void Shutdown();

	//renders all the sprites
	static void Render();
};

#endif