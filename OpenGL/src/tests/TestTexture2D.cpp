#include "TestTexture2D.h"
#include "GL/glew.h"
#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {
	
	TestTexture2D::TestTexture2D()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), 
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_TranslationA(200,200,0),
		m_TranslationB(400,200,0)
		{	

		float positions[] = {
			-150.0,-150.0f, 0.0f, 1.0f,
			150.0f, -150.0f, 1.0f, 0.0f,
			150.0f, 150.0f, 1.0f, 1.0f,
			-150.0f, 150.0f, 0.0f, 1.0f

			- 150.0f+200,-150.0f+100, 0.0f, 1.0f,
			150.0f+200, -150.0f+100, 1.0f, 0.0f,
			150.0f+200, 150.0f+100, 1.0f, 1.0f,
			-150.0f+200, 150.0f+100, 0.0f, 1.0f
		};

		unsigned int indices[] =
		{	0,1,2,
			2,3,0, 
			4,5,6,
			6,7,4,
		};

		GLCall(glEnable(GL_BLEND)); // Enable transparency a.k.a Blending in OpenGL
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // final color = source alpa + (1-source alpha)
		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 2*4*4*sizeof(float));
		m_VAO = std::make_unique<VertexArray>();
		VertexBufferLayout layout;

		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

	
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		m_Texture = std::make_unique<Texture>("res/textures/ChernoLogo.png");
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

	}

	void TestTexture2D:: OnRender()
	{
		GLCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		m_Texture->Bind();



		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
		//{
		//	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
		//	glm::mat4 mvp = m_Proj * m_View * model;
		//	m_Shader->Bind();
		//	m_Shader->SetUniformMat4f("u_MVP", mvp);
		//	renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

		//}
	}
	void TestTexture2D:: OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
		//ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
		
	}

	TestTexture2D::~TestTexture2D()
	{

	}
	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

}