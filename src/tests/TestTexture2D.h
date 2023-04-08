#ifndef __TEST_TEXTURE2D_H
#define __TEST_TEXTURE2D_H

#include "test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"

#include <memory>

namespace test {

	class TestTexture2D : public Test {
	public:
		TestTexture2D();
		~TestTexture2D();
		
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
		glm::vec3 m_translationA, m_translationB;
	};

}

#endif