#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "tests/TestClearColor.h"   

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Use the core profile to enforce our own implementation of a vertex array
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Synchronize the refresh rate with our native refresh rate
    glfwSwapInterval(1);

    // Initialize Glew
    if (glewInit() != GLEW_OK)
        std::cout << "glewInit error!" << std::endl;

    // Log the OpenGL version used because we can
    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        // Create and select (bind) the data & buffer for drawing


        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        Renderer renderer;
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        test::TestClearColor test;

        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            test.OnUpdate(0.0f);
            test.OnRender();

            ImGui_ImplGlfwGL3_NewFrame();
            test.OnImGuiRender();
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());


            GLCall(glfwSwapBuffers(window)); 
            GLCall(glfwPollEvents()); 
        }
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

//{
//    static float f = 0.0f;
//   // Display some text (you can use a format string too)
//    ImGui::SliderFloat3("float#1", &translationA.x, 0.0f, 960.0f);
//    ImGui::SliderFloat3("float#2", &translationB.x, 0.0f, 960.0f);
//    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//}

            //// Animate the r value between 0.0 and 1.0
            //if (r > 1.0f)
            //    increment = -0.05f;
            //else if (r < 0.0f)
            //    increment = 0.05f;
            //r += increment;

 /* {
  glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
  glm::mat4 mvp = proj * view * model;
  //shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
  shader.SetUniformMat4f("u_MVP", mvp);
  renderer.Draw(va, ib, shader);
            }
  {
      glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
      glm::mat4 mvp = proj * view * model;
      //shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
      shader.SetUniformMat4f("u_MVP", mvp);
      renderer.Draw(va, ib, shader);
  }

        VertexArray va; // Initialize our vertex array

        VertexBuffer vb(positions, 4 * 4 * sizeof(float)); // Create and bind a buffer for the vertices

        VertexBufferLayout layout; // Create a layout for the buffer we created
        layout.Push<float>(2);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6); // Create and bind a buffer for the indices

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


        Texture texture("res/textures/ChernoLogo.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();
          glm::vec3 translationA(200, 200, 0);
        glm::vec3 translationB(100, 100, 0);
  
  bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);



        // Animation stuff
        float r = 0.0f;
        float increment = 0.05f;*/
