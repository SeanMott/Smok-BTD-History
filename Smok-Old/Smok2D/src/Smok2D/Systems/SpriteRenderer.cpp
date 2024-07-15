#include <smpch.h>
#include "SpriteRenderer.h"

#include <Core\AssetManager.h>
#include <Core\ECS\EntityManager.h>
#include <Core\ECS\Components\Transform.h>
#include "Smok2D\Components\OrthographicCamera.h"
#include "Smok2D\Components\Sprite.h"

#include <Renderer\Display.h>
#include <Renderer\BufferLayout.h>
#include <Core\Events\EngineEvents.h>

#include <gtc/matrix_transform.hpp>

using namespace glm; using namespace std;

Shader* SpriteRenderer::lastShader = nullptr;
Texture* SpriteRenderer::lastTexture = nullptr;

string SpriteRenderer::lastShaderName = "";
string SpriteRenderer::lastTextureName = "";

VertexBuffer* SpriteRenderer::spriteBuffer = nullptr;
IndexBuffer* SpriteRenderer::spriteIndexBuffer = nullptr;
bool SpriteRenderer::hasSentWarning = false;

GraphicContext* SpriteRenderer::context = nullptr;

//sets the sprite renderer and links it
void SpriteRenderer::Init()
{
#ifdef DISABLE_SMOK_2D
	return;
#endif

	context = DisplayI.GetContext();

	float vertices[] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2, 
		2, 3, 0
	};

	BufferLayout layout = {
		{ShaderDataType::Float3, "vertex"},
		{ShaderDataType::Float2, "tex"}
	};

	spriteBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
	spriteBuffer->SetLayout(layout);
	spriteIndexBuffer = IndexBuffer::Create(indices, sizeof(indices));

	ECSSystemEvent::AddMethod(&SpriteRenderer::Render);
}

//shuts down the sprite renderer
void SpriteRenderer::Shutdown()
{
	if(spriteBuffer)
		spriteBuffer->Destroy();
	if (spriteIndexBuffer)
		spriteIndexBuffer->Destroy();

	//remove Render from the system event call
}

//renders all the sprites
void SpriteRenderer::Render()
{
	mat4 model = mat4(1.0f);
	mat4 projection = mat4(1.0f);
	mat4 view = mat4(1.0f);
	mat4 projectionView = mat4(1.0f);

	if (hasSentWarning)
		return;

	if (!spriteBuffer && !hasSentWarning)
	{
		Logger::LogErrorAlways("Sprite Renderer", "Sprite Buffer was not initialised properly, make sure DISABLE_SMOK_2D was not defined and or project settings enable Smok 2D.");
		hasSentWarning = true;
		return;
	}

	if (!spriteIndexBuffer && !hasSentWarning)
	{
		Logger::LogErrorAlways("Sprite Renderer", "Sprite Index Buffer was not initialised properly, make sure DISABLE_SMOK_2D was not defined and or project settings enable Smok 2D.");
		hasSentWarning = true;
		return;
	}

	spriteBuffer->Bind();
	spriteIndexBuffer->Bind();

	//gets camera
	auto c = EntityManager::GetReg().view<OrthographicCamera, Transform>();
	if (c.size() < 1)
	{
		Logger::LogErrorAlways("Sprite Renderer", "No Orhtographic Camera components were found, at least put one but make it inactive if you don't want it.");
		hasSentWarning = true;
		return;
	}

	for (auto cam : c)
	{
		auto& camera = c.get<OrthographicCamera>(cam);
		if (!camera.isActive)
			continue;

		auto& trans = c.get<Transform>(cam);

		projection = ortho(0.0f, camera.viewLength, camera.viewHeight, 0.0f, -1.0f, 1.0f);
		
		mat4 transform = translate(mat4(1.0f), trans.position) * 
			rotate(mat4(1.0f), trans.rotation.x, vec3(0.0f, 0.0f, 1.0f));

		view = inverse(transform);
		projectionView = projection * view;
	}

	//render entities
	auto entities = EntityManager::GetReg().view<Sprite, Transform>();

	for (auto entity : entities)
	{
		auto& sprite = entities.get<Sprite>(entity);
		if (!sprite.isActive)
			continue;
		auto& trans = entities.get<Transform>(entity);

		if (lastShaderName != sprite.shader)
		{
			lastShaderName = sprite.shader;
			lastShader = AssetManager::GetShader(lastShaderName);
			if (lastShader == nullptr)
			{
				Logger::LogMessage("Not all entites with a active Sprite component has a shader assigned.");
				continue;
			}

			lastShader->Bind();
		}

		if (lastTextureName != sprite.texture)
		{
			lastTextureName = sprite.texture;
			lastTexture = AssetManager::GetTexture(lastTextureName);
			
			if (lastTexture == nullptr)
			{
				Logger::LogMessage("Not all entites with a active Sprite component has a texture assigned.");
				continue;
			}

			lastTexture->Bind(sprite.textureSlot);
		}

		//cal transform
		model = mat4(1.0f);
		model = translate(model, trans.position) *
			rotate(model, radians(trans.rotation.x), vec3(0.0f, 0.0f, 1.0f)) *
			scale(model, trans.scale * 50.0f);

		if (lastShader)
		{
			lastShader->SetInt("Sprite", sprite.textureSlot);
			lastShader->SetVector3("Color", sprite.color);
			lastShader->SetMatrix4("PVM", projection * view * model);
		}

		//draw call
		context->IndexBufferDrawCall(0, spriteIndexBuffer->GetCount());
	}
}

	/*

	----Note----
	add batch rendering later
	----Note----

	*/