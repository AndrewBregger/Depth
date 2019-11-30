#include "window.hpp"

void error_callback(i32 error, const char* msg) {
    LOG_ERR("GLFW ERROR: {} | {}", error, msg);
}

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                                     GLenum severity, GLsizei length,
                                     const GLchar *msg, const void *data)
{
    const char* _source;
    const char* _type;
    const char* _severity;
    
    switch (source) {
        case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;
        
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;
        
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;
        
        case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;
        
        case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;
        
        case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;
        
        default:
        _source = "UNKNOWN";
        break;
    }
    
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;
        
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;
        
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;
        
        case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;
        
        case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;
        
        case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;
        
        case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;
        
        default:
        _type = "UNKNOWN";
        break;
    }
    
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;
        
        case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;
        
        case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;
        
        case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;
        
        default:
        _severity = "UNKNOWN";
        break;
    }
    
    LOG_ERR("%d: %s of %s severity, raised from %s: %s\n",
            id, _type, _severity, _source, msg);
}



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
    
	void Window::create_glwindow(const std::string& title, u32 width, u32 height,
			const glm::ivec2& position, bool fullscreen) {

		this->title = title;
		this->width = width;
		this->height = height;
		this->position = position;
		this->fullscreen = fullscreen;
        
        glfwSetErrorCallback(error_callback);
		
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

		std::cout << width << ", " << height << std::endl;

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
        
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(GLDebugMessageCallback, NULL);
        
		unset_context();
	}
    
    
	void Window::make_current() {
		glfwMakeContextCurrent(handle);
	}
	
	void Window::unset_context() {
		glfwMakeContextCurrent(nullptr);
	}
}
