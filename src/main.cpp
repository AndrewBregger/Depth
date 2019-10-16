#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>

#include "common.hpp"
#include "window.hpp"
#include "input.hpp"
#include "events.hpp"

void render() {
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, 0.0);

	glVertex3f(-0.5, -0.5, 0.0);
	
	glVertex3f(0.5, 0.5, 0.0);

	glVertex3f(-0.5, 0.5, 0.0);

	glEnd();
}

/// main render loop.
void gmain() {
	auto window = win::Window();

	window.make_current();

	event::EventManager emanager(&window);

	glClearColor(1.0, 1.0, 1.0, 1.0);

	while(!glfwWindowShouldClose(window.get_handle())) {

		emanager.process_events();

		glClear(GL_COLOR_BUFFER_BIT);
		
		render();

		window.swapbuffers();
	}
}

int main() {
	utils::logging::init_logger();

	std::thread main_loop(gmain);	
	
	main_loop.join();


	return 0;
}
