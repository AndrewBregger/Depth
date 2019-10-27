#include <thread>

#include "common.hpp"
#include "window.hpp"
#include "events/input.hpp"
#include "events/events.hpp"
#include "listener/camera_listener.hpp"
#include "listener/window_listener.hpp"

#include "image.hpp"
#include "texture.hpp"

void render() {
	glBegin(GL_TRIANGLE_STRIP);

	// glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, 0.0);
	glTexCoord2f(1.0, 0.0);

	glVertex3f(-0.5, -0.5, 0.0);
	glTexCoord2f(0.0, 0.0);
	
	glVertex3f(0.5, 0.5, 0.0);
	glTexCoord2f(1.0, 1.0);

	glVertex3f(-0.5, 0.5, 0.0); 
	glTexCoord2f(0.0, 1.0);
	glEnd();
}

/// main render loop.
void gmain() {
	LOG_INFO("App Start");
	auto window = win::Window();

	LOG_INFO("App Setup");
	view::Camera camera;
	camera.set_position(glm::vec2(0, 0));
	camera.set_rotation(0.0f);

	window.make_current();

	event::EventManager emanager(&window);
	listener::WindowListener wlist(&window);
	listener::CameraListener clist(&camera);

	emanager.register_callback(event::WindowResizeEvent, &wlist, [](Listener* listener) {
				auto w = (listener::WindowListener*) listener;
				auto size = event::Input::window_resize();
				w->window->set_size(size.x, size.y);
			});

	emanager.register_callback(event::WindowResizeEvent, &wlist, [](Listener* listener) {
				auto c = (listener::CameraListener*) listener;
				auto size = event::Input::window_resize();
				c->camera->set_size(size.x, size.y);
			});

	LOG_INFO("Post Setup");

	res::Image image = res::Image::from_file("./res/test.jpg");

	gfx::Texture texture(image);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);

	while(!glfwWindowShouldClose(window.get_handle())) {

		emanager.process_events();

		glClear(GL_COLOR_BUFFER_BIT);

		texture.activate();
		texture.bind();
		
		render();

		texture.unbind();

		window.swapbuffers();
	}
}

int main() {
	utils::logging::init_logger();

	std::thread main_loop(gmain);	
	
	main_loop.join();

	return 0;
}
