#include "window.hpp"

namespace win {

	bool Window::glfw_initiated = false;

	Window::Window() {
		create_glwindow("Game", WINDOW_WIDTH, WINDOW_HEIGHT, {0, 0}, false);
	}

	Window::~Window() {
		if(handle) {
			glfwDestroyWindow(handle);
			glfwTerminate();
			handle = nullptr;
		}
	}

	void Window::create_glwindow(const std::string& title, 
			u32 width, u32 height, const glm::ivec2& position, bool fullscreen) {
		this->title = title;
		this->width = width;
		this->height = height;
		this->position = position;
		this->fullscreen = fullscreen;
		
		if(!glfw_initiated) {
			if(!glfwInit()) {
				LOG_ERR("Failed to initialize glfw");
				exit(1);
			}
			glfw_initiated = true;
		}
		GLFWmonitor* monitor = nullptr;
		if(fullscreen) {
			// handle monitor
		}
		
		auto window = glfwCreateWindow(width, height, this->title.c_str(), monitor, nullptr);

		if(window == nullptr) {
			LOG_ERR("Failed to create window");
			glfwTerminate();
			exit(1);
		}

		glfwMakeContextCurrent(window);

		if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
			LOG_ERR("Failed to initialize OpenGL Context");
			exit(1);
		}

		this->handle = window;
		this->monitor = monitor;

		// set the windows position
		glfwSetWindowPos(handle, position.x, position.y);

		unset_context();
	}


	void Window::make_current() {
		glfwMakeContextCurrent(handle);
	}
	
	void Window::unset_context() {
		glfwMakeContextCurrent(nullptr);
	}
}
