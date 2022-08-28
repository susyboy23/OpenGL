#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


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