#pragma once
#include<string>
#include<unordered_map>
/**
	A struct that combines shader sources (file location) into a single type.
*/
struct ShaderProgramSource
{
	std::string VertexSource; // for vertex shader
	std::string FragmentSource; // for fragment shader
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set uniforms
	void SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
private:
	unsigned int GetUniformLocation(const std::string& name);
	ShaderProgramSource ParseShader(const std::string filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};
