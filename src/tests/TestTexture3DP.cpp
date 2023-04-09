#include "TestTexture3DP.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "imgui.h"


namespace test {

	TestTexture3DP::TestTexture3DP() :
		m_Radians{ 0.0f, 0.0f, 0.0f },
		m_Proj(glm::perspective(glm::radians(50.0f), (float)1280 / (float)800, 0.0f, 100.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)))
	{
	    float position[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f};

		GLuint indices[] = {
			0 , 1 , 3,
			1 , 2 , 3
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);
	
		
		/* VAO && VBO */
		m_VBO = std::make_unique <VertexBuffer>(position, 5 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
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

	TestTexture3DP::~TestTexture3DP()
	{
	
	}

	void TestTexture3DP::OnUpdate(float deltaTime)
	{

	}

	void TestTexture3DP::OnRender()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer renderer;
		m_Texture->Bind(1);

		{

			glm::mat4 model_x = glm::rotate(glm::mat4(1.0f), glm::radians(m_Radians[0]), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 model_y = glm::rotate(glm::mat4(1.0f), glm::radians(m_Radians[1]), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 model_z = glm::rotate(glm::mat4(1.0f), glm::radians(m_Radians[2]), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 mvp = m_Proj * m_View * model_x * model_y * model_z;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
	}

	void TestTexture3DP::OnImGuiRender()
	{
		
		ImGui::SliderFloat("X", &m_Radians[0], -90.0f, 90.0f);
		ImGui::SliderFloat("Y", &m_Radians[1], -90.0f, 90.0f);
		ImGui::SliderFloat("Z", &m_Radians[2], -90.0f, 90.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 
		1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}