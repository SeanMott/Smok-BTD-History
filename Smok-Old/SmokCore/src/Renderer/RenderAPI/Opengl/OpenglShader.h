//the opengl implementation of the shader

#ifndef OpenglShader_h
#define OpenglShader_h

#include <Renderer\Assets\Shader.h>

#include <unordered_map>

#include <glad\glad.h>

class OpenglShader : public Shader
{
	//vars
private:

	unsigned int id;

	std::unordered_map<std::string, int> uniforms; //name, location

	//methods
public:

	//Constructor || vertex and fragment
	OpenglShader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	//Constructor || geometry
	//OpenglShader(const std::string& geometryFilePath);
	//Constructor || compute
	//OpenglShader(const std::string& computeFilePath);

	virtual ~OpenglShader() { Destroy(); }

	// Inherited via Shader
	void Destroy() override { glDeleteProgram(id); }
	inline void Bind() const override { glUseProgram(id); }
	inline void Unbind() const override { glUseProgram(0); }

	inline void SetBool(const std::string& name, bool value) override { glUniform1i(GetLocation(name), (int)value); }
	inline void SetInt(const std::string& name, int value) override { glUniform1i(GetLocation(name), value); }
	inline void SetUnsignedInt(const std::string& name, unsigned int value) override { glUniform1ui(GetLocation(name), value); }
	inline void SetFloat(const std::string& name, float value) override { glUniform1f(GetLocation(name), value); }


	inline void SetVector2(const std::string& name, const glm::vec2& value) override { glUniform2fv(GetLocation(name), 1, &value[0]); }
	inline void SetVector2(const std::string& name, float x, float y) override { glUniform2f(GetLocation(name), x, y); }

	inline void SetVector3(const std::string& name, const glm::vec3& value) override { glUniform3fv(GetLocation(name), 1, &value[0]); }
	inline void SetVector3(const std::string& name, float x, float y, float z) override { glUniform3f(GetLocation(name), x, y, z); }

	inline void SetVector4(const std::string& name, const glm::vec4& value) override { glUniform4fv(GetLocation(name), 1, &value[0]); }
	inline void SetVector4(const std::string& name, float x, float y, float z, float w) override { glUniform4f(GetLocation(name), x, y, z, w); }

	inline void SetMatrix2(const std::string& name, const glm::mat2& value) override { glUniformMatrix2fv(GetLocation(name), 1, GL_FALSE, &value[0][0]); }
	inline void SetMatrix3(const std::string& name, const glm::mat3& value) override { glUniformMatrix3fv(GetLocation(name), 1, GL_FALSE, &value[0][0]); }
	inline void SetMatrix4(const std::string& name, const glm::mat4& value) override { glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, &value[0][0]); }

private:

	//gets the uniform location
	int GetLocation(const std::string& name);
	//compiles a shader of any type || for now errors only support vertex and fragment
	unsigned int CompileShader(unsigned int type, const std::string& source);
};

#endif