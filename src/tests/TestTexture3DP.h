#ifndef __TEST_TEXTURE3DP_H
#define __TEST_TEXTURE3DP_H

#include "test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"

#include <memory>

namespace test {

	class TestTexture3DP : public Test {
	public:
		TestTexture3DP();
		~TestTexture3DP();
		
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr <VertexArray> m_VAO;
		std::unique_ptr <VertexBuffer> m_VBO;
		std::unique_ptr <IndexBuffer> m_IBO;
		std::unique_ptr <Shader> m_Shader;
		std::unique_ptr <Texture> m_Texture;
		
		glm::mat4 m_Proj, m_View;
		float m_Radians[3];
	};

}

#endif