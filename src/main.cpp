#include <thread>

#include "common.hpp"
#include "window.hpp"
#include "events/input.hpp"
#include "events/events.hpp"
#include "listener/camera_listener.hpp"
#include "listener/window_listener.hpp"

#include "image.hpp"
#include "texture.hpp"
#include "shader.hpp"

extern std::shared_ptr<utils::logging::Logger> logger;

void render(gfx::Shader& shader, u32 vao, u32 vbo, u32 ibo) {
	glCheck(shader.use());
	glCheck(glBindVertexArray(vao));
		
	glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

	glCheck(glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, nullptr));

	glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	glCheck(glBindVertexArray(0));
	glCheck(shader.unuse());
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

	// image = image.convert_to(PixelFormat::Rgba);

	gfx::Texture texture(image);

	gfx::Shader shader("quad", "./res/shaders/quad_vs.glsl", "./res/shaders/quad_fs.glsl",
				std::optional("./res/shaders/quad_gs.glsl"));


	u32 vao, vbo, ibo;
	glCheck(glGenVertexArrays(1, &vao));

	glCheck(glGenBuffers(1, &vbo));
	glCheck(glGenBuffers(1, &ibo));

	glCheck(glBindVertexArray(vao));

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	struct Vertex {
		glm::vec4 quadInfo;
		glm::vec4 texInfo;
		glm::vec4 colorMask;
	};

	Vertex data[1] = {
		Vertex {
			.quadInfo	= {-0.5, -0.5, 1.0, 1.0},
			.texInfo	= {0.0, 0.0, 1.0, 1.0},
			.colorMask	= {1.0, 1.0, 1.0, 1.0}
		}
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	u32 indicies[] = {0};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32), indicies, GL_STATIC_DRAW);

	u64 attributeSizes[] = {4, 4, 4};
	u64 stride = 0;

	for(u32 i = 0; i < 3; ++i) {
		glVertexAttribPointer(i, attributeSizes[i], GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (stride * sizeof(f32)));
		glEnableVertexAttribArray(i);
		stride += attributeSizes[i];
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glCheck(glBindVertexArray(0));

	glClearColor(1.0, 1.0, 1.0, 1.0);

	texture.activate();

	shader.add_texture("tex", texture);

	while(!glfwWindowShouldClose(window.get_handle())) {
		emanager.process_events();
		glCheck(glClear(GL_COLOR_BUFFER_BIT));

		texture.bind();
		render(shader, vao, vbo, ibo);
		texture.unbind();

		window.swapbuffers();
	}
}

int main() {
	utils::logging::init_logger();

	logger->send_to_console(true);

	gmain();

	// std::thread main_loop(gmain);	
	
	// main_loop.join();

	return 0;
}
