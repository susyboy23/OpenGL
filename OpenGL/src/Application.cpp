#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glShaderSource.xhtml
    glCompileShader(id);
    // TODO:  Error Handling

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;

    }
    return id;

    

}
static int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{   
    // glCreateProgram creates an empty program object and returns a non-zero value by which it can be referenced. 
    // A program object is an object to which shader objects can be attached. 
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    // glValidateProgram checks to see whether the executables contained in program can execute given the current OpenGL state.
    glValidateProgram(program);
    // This command effectively undoes the effects of a call to glCreateShader.
    glDeleteShader(vs);
    glDeleteShader(fs);
   
    return program;

}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error\n";
    }
    // info based on which triangles are to be drawn
    float positions[6] = {
           1.0f, 0.0f
            ,0.0f, 0.5f
            ,0.5f, -0.5f
    };
    unsigned int buffer; // an int to store the ID of the created buffer object
    glGenBuffers(1, &buffer); // create a buffer and store its ID into uint buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // declare that the created buffer object, with ID = buffer, is gonna be an array
    // structure of the array, size of the buffer, starting point of the data, hint: gonna be used to draw infrequently
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); // describe that array

    // attribute index, num of values, type of values, no normalization, size of attribute, distance from first attribute
    glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE,sizeof(float)*2,0); // create attribute buffer
    glEnableVertexAttribArray(0); // enable the state

    std::string fragmentShader = "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(0.3f,0.01f, 0.2f,1.0);\n"
        "}\n";
    std::string vertexShader = "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = position;\n"
        "}\n";
    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES,3,)
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}