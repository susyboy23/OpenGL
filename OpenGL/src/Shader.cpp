#include "Shader.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include "Renderer.h"
Shader::Shader(const std::string& filename)
    :m_FilePath(filename), m_RendererID(0){
	
    ShaderProgramSource source = ParseShader(filename);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID)); // bind the shader
}

void Shader::Unbind() const
{
    GLCall(glDeleteProgram(0)); // Clean up the the program with shaders
}

void Shader::SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4)
{
    GLCall(glUniform4f(GetUniformLocation(name), f1, f2, f3, f4));
    
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{   
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
    {
        std::cout<<"Error";
    }
     m_UniformLocationCache[name] = location;

    return location;
}
/**
    Parse a single shader file to a shader source.

    @param filePath Path to the shader file
    @return ShaderProgramSource The combined shader sources in as ShaderProgramSource
*/
ShaderProgramSource Shader::ParseShader(const std::string filePath)
{
    std::ifstream stream(filePath);

    enum class Shadertype
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2]; // 2 for vertex and fragment shaders
    Shadertype type = Shadertype::NONE;

    while (getline(stream, line))
    {
        // Set the type if #shader is found
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = Shadertype::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = Shadertype::FRAGMENT;
        }
        else // Add the line to the source
        {
            ss[(int)type] << line << '\n';
        }
    }

    // end result is a stringstream array, 
    // element 0 -> vertex shader code, element 1-> fragment shader code
    return { ss[0].str(), ss[1].str() };
}

/**
    Compiles a single shader so it can be attached.

    @param type The type of the shader
    @param source The source code of the shader as string
    @return unsigned int An identifier for the compiled shader
*/
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type); // Create the shader
    const char* src = source.c_str(); // Return the pointer of the first character of the source
    GLCall(glShaderSource(id, 1, &src, nullptr)); // Specify the shader source code
    GLCall(glCompileShader(id));

    // Error handling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); // Returns the compile status parameter
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char)); // Allocate this on the stack dynamically because 'char message[length]' is not allowed
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}


/**
    Links the given shaders into a single shader so that it can be bound.

    @param vertexShader Source of the vertexshader as string
    @param fragmentShader Source of the fragmentshader as string
    @return unsigned int An identifier for the newly created shader
*/
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram(); // Create a shader program to attach shader to
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // Attach both shaders to the program
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program)); // Link the program so the shaders are used
    GLCall(glValidateProgram(program)); // Check if the program can be executed

    // The shaders are linked to the progam, so the shaders can be deleted
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}



