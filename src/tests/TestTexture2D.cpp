#include "TestTexture2D.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "imgui.h"


namespace test {

	TestTexture2D::TestTexture2D() :
		m_translationA(0.0f, 0.0f, 0.0f),
		m_translationB(50.0f, 150.0f, 0.0f),
		m_Proj(glm::ortho(0.0f, 400.0f, 0.0f, 300.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		float position[] = {
		-50.0f, -50.0f, 0.0f, 0.0f,
		 50.0f, -50.0f, 1.0f, 0.0f,
		 50.0f,  50.0f, 1.0f, 1.0f,
		-50.0f,  50.0f, 0.0f, 1.0f};

		GLuint indices[] = {
			0 , 1 , 2,
			2 , 3 , 0
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);
	
		
		/* VAO && VBO */
		m_VBO = std::make_unique <VertexBuffer>(position, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		
		m_VAO = std::make_unique <VertexArray>();
		m_VAO->AddBuffer(*m_VBO, layout);

		/* IBO */
		m_IBO = std::make_unique<IndexBuffer>(indices, 6);

		/* shaderer */
		m_Shader = std::make_unique <Shader>("../res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 1);

		/* texture */
		m_Texture = std::make_unique<Texture>("../res/textures/tiandeng.png");
	}

	TestTexture2D::~TestTexture2D()
	{
	
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer renderer;
		m_Texture->Bind(1);

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
	
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}

	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("A", &m_translationA.x, 0.0f, 300.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat3("B", &m_translationB.x, 0.0f, 300.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 
			1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
