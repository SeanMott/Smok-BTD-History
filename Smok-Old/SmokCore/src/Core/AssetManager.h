//defines a asset manager

#ifndef AssetManager_h
#define AssetManager_h

#include <string>
#include <unordered_map>

#include <Renderer\Assets\Shader.h>
#include <Renderer\Assets\Texture.h>

class AssetManager
{
	//vars
private:

	static std::unordered_map<std::string, Shader*> shaders;
	static std::unordered_map<std::string, Texture*> textures;

	//methods
public:

	//loads a shader || vertex and fragment
	static void LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
	//loads a shader || geometry
	static void LoadGeometryShader(const std::string& name, const std::string& geometryPath);
	//loads a shader || compute
	static void LoadComputeShader(const std::string& name, const std::string& computePath);
	//destroys a shader
	static void DestroyShader(const std::string& name);
	//gets a shader by name
	static Shader* GetShader(const std::string& name);

	//loads a texture
	static void LoadTexture(const std::string& name, const std::string& path);
	//destroys a texture
	static void DestroyTexture(const std::string& name);
	//gets a texture by name
	static Texture* GetTexture(const std::string& name);
	//gets all Textures
	static inline std::unordered_map<std::string, Texture*>& GetAllTextures() { return textures; }

	//destroys all shaders
	static void DestroyAllShaders();
	//destroys all textures
	static void DestroyAllTextures();

	//destroys all assets
	static void DestroyAllAssets();

private:

	//returns if a shader exists
	static bool IsShader(const std::string& name);
	//returns if a texture exists
	static bool IsTexture(const std::string& name);
};

#endif