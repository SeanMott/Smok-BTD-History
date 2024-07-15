//base shader

#ifndef Shader_h
#define Shader_h

#include <string>
#include <glm.hpp>

class Shader
{
public:

	//creates a shader || vertex and fragment
	static Shader* Create(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	//creates a shader || geometry
	static Shader* CreateGeometry(const std::string& geometryFilePath);
	//creates a shader || compute
	static Shader* CreateCompute(const std::string& computeFilePath);

	virtual ~Shader() {}

	//returns the source of a file
	static std::string GetSource(const std::string& filePath);

	//destroys a shader
	virtual void Destroy() = 0;

	//binds the shader
	virtual void Bind() const = 0;
	//unbinds the shader
	virtual void Unbind() const = 0;

	//sets a uniform
	virtual void SetBool(const std::string& name, bool value) = 0;
	virtual void SetInt(const std::string& name, int value) = 0;
	virtual void SetUnsignedInt(const std::string& name, unsigned int value) = 0;
	virtual void SetFloat(const std::string& name, float value) = 0;

	virtual void SetVector2(const std::string& name, const glm::vec2& value) = 0;
	virtual void SetVector2(const std::string& name, float x, float y) = 0;
	
	virtual void SetVector3(const std::string& name, const glm::vec3& value) = 0;
	virtual void SetVector3(const std::string& name, float x, float y, float z) = 0;
	
	virtual void SetVector4(const std::string& name, const glm::vec4& value) = 0;
	virtual void SetVector4(const std::string& name, float x, float y, float z, float w) = 0;

	virtual void SetMatrix2(const std::string& name, const glm::mat2& value) = 0;
	virtual void SetMatrix3(const std::string& name, const glm::mat3& value) = 0;
	virtual void SetMatrix4(const std::string& name, const glm::mat4& value) = 0;
};

#endif