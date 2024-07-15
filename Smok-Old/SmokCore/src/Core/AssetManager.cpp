#include "smpch.h"
#include "AssetManager.h"

using namespace std;

unordered_map<string, Shader*> AssetManager::shaders;
unordered_map<string, Texture*> AssetManager::textures;

void AssetManager::LoadShader(const string& name, const string& vertexPath, const string& fragmentPath)
{
	if (IsShader(name))
	{
		Logger::LogErrorAlways("Asset", name + " is already a shader.");
		return;
	}

	shaders[name] = Shader::Create(vertexPath, fragmentPath);
}

void AssetManager::LoadGeometryShader(const string& name, const string& geometryPath)
{
	if (IsShader(name))
	{
		Logger::LogErrorAlways("Asset", name + " is already a shader.");
		return;
	}

	shaders[name] = Shader::CreateGeometry(geometryPath);
}

void AssetManager::LoadComputeShader(const string& name, const string& computePath)
{
	if (IsShader(name))
	{
		Logger::LogErrorAlways("Asset", name + " is already a shader.");
		return;
	}

	shaders[name] = Shader::CreateCompute(computePath);
}

void AssetManager::DestroyShader(const string& name)
{
	if (!IsShader(name))
	{
		Logger::LogErrorAlways("Asset", name + " is not a shader.");
		return;
	}

	shaders[name]->Destroy();
	shaders.erase(name);
}

Shader* AssetManager::GetShader(const string& name)
{
	if (!IsShader(name))
	{
		Logger::LogErrorAlways("Asset", name + " is not a shader.");
		return nullptr;
	}

	return shaders[name];
}

void AssetManager::LoadTexture(const string& name, const string& path)
{
	if (IsTexture(name))
	{
		Logger::LogErrorAlways("Asset", name + " is not a texture.");
		return;
	}

	textures[name] = Texture::Create(path);
}

void AssetManager::DestroyTexture(const string& name)
{
	if (!IsTexture(name))
	{
		Logger::LogErrorAlways("Asset", name + " is not a texture.");
		return;
	}

	textures[name]->Destroy();
	textures.erase(name);
}

Texture* AssetManager::GetTexture(const string& name)
{
	if (!IsTexture(name))
	{
		Logger::LogErrorAlways("Asset", name + " is not a texture.");
		return nullptr;
	}

	return textures[name];
}

void AssetManager::DestroyAllShaders()
{
	if (shaders.size() < 1)
		return;

	for (auto asset : shaders)
	{
		asset.second->Destroy();
	}

	shaders.clear();
}

void AssetManager::DestroyAllTextures()
{
	if (textures.size() < 1)
		return;

	for (auto asset : textures)
	{
		asset.second->Destroy();
	}

	textures.clear();
}

void AssetManager::DestroyAllAssets()
{
	DestroyAllShaders();
	DestroyAllTextures();
}

bool AssetManager::IsShader(const string& name)
{
	for (auto asset : shaders)
	{
		if (asset.first == name)
			return true;
	}

	return false;
}

bool AssetManager::IsTexture(const string& name)
{
	for (auto asset : textures)
	{
		if (asset.first == name)
			return true;
	}

	return false;
}
