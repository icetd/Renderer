#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Texture.h"
#include "log.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int LogLevel;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	initLogger(NOTICE);
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 800, "Renderer", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LOG(ERROR, "Failed to initialize GLAD");
		return -1;
	}

	LOG(NOTICE, "%s\n", glGetString(GL_VERSION));

	float position[] = {
		 -50.0f, -50.0f, 0.0f, 0.0f,
		  50.0f, -50.0f, 1.0f, 0.0f,
		  50.0f,  50.0f, 1.0f, 1.0f,
		 -50.0f,  50.0f, 0.0f, 1.0f
	};

	GLuint indices[] = {
		0 , 1 , 2,
		2 , 3 , 0
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);


	/* VAO && VBO */
	VertexArray va;
	VertexBuffer vb(position, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	/* IBO */
	IndexBuffer ib(indices, 6);
	
	glm::mat4 proj = glm::ortho(-400.0f, 400.0f, -400.0f, 400.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	glm::mat4 mvp = proj * view;

	/* shaderer */
	Shader shader("../res/shaders/Basic.shader");
	shader.Bind();
	shader.SetUniform1i("u_Texture", 1);
	shader.SetUniformMat4f("u_MVP", mvp);


	/* texture */
	Texture texture("../res/textures/tiandeng.png");
	texture.Bind(1);

	va.UnBind();
	vb.Unbind();
	ib.Unbind();
	shader.UnBind();

	Renderer renderer;


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();
		shader.Bind();
		texture.Bind(1);
		renderer.Draw(va, ib, shader);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}