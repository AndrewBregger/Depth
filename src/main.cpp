#include "common.hpp"
#include <GLFW/glfw3.h>

int main() {
	utils::logging::init_logger();

	glfwInit();

	auto window = glfwCreateWindow(500, 400, "Depth", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
