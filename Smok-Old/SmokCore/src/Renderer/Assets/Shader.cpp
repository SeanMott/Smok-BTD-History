#include <smpch.h>
#include "Shader.h"

#include <Renderer\RenderAPI\RenderAPI.h>
#include <Renderer\RenderAPI\Opengl\OpenglShader.h>
//#include <Renderer\RenderAPI\Vulkin\VulkinShader.h>
//#include <Renderer\RenderAPI\DirectX\DirectXShader.h>
//#include <Renderer\RenderAPI\Metal\MetalShader.h>

#include <fstream>

using namespace std;

//creates a shader || vertex and fragment
Shader* Shader::Create(const string& vertexFilePath, const string& fragmentFilePath)
{
	RenderAPIType type = RenderAPI::GetAPI();

	if (type == RenderAPIType::Vulkin)
	{
		Logger::LogErrorAlways("Shader", "Vulkin is currently not supported, Opengl will be used.");
		//return new VulkinShader(vertexFilePath, fragmentFilePath);
		return new OpenglShader(vertexFilePath, fragmentFilePath);
	}

	else if (type == RenderAPIType::DirectX)
	{
		Logger::LogErrorAlways("Shader", "DirectX is currently not supported, Opengl will be used.");
		//return new DirectXShader(vertexFilePath, fragmentFilePath);
		return new OpenglShader(vertexFilePath, fragmentFilePath);
	}

	else if (type == RenderAPIType::Metal)
	{
		Logger::LogErrorAlways("Shader", "Metal is currently not supported, Opengl will be used.");
		//return new MetalShader(vertexFilePath, fragmentFilePath);
		return new OpenglShader(vertexFilePath, fragmentFilePath);
	}

	else
		return new OpenglShader(vertexFilePath, fragmentFilePath);
}

//creates a shader || geometry
Shader* Shader::CreateGeometry(const string& geometryFilePath)
{
	Logger::LogErrorAlways("Shader", "Geometry shaders are currently not supported, please check GitHub for updates.");
	return nullptr;
}

//creates a shader || compute
Shader* Shader::CreateCompute(const string& computeFilePath)
{
	Logger::LogErrorAlways("Shader", "Compute shaders are currently not supported, please check GitHub for updates.");
	return nullptr;
}

//returns the source of a file
string Shader::GetSource(const string& filePath)
{
	string source = "";
	ifstream readStream(filePath);
	if (!readStream.is_open())
	{
		Logger::LogErrorAlways("Shader", "Failed to open " + filePath + ". Make sure file is there.");
		return "";
	}

	readStream.seekg(0, ios::end);
	source.resize(readStream.tellg());
	readStream.seekg(0, ios::beg);
	readStream.read(&source[0], source.size());
	readStream.close();

	return source;
}