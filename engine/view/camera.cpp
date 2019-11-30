#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "window.hpp"

namespace view {
	Camera::Camera(const win::Window& window) : dirty(true) {
		set_aspect_ratio((f32) window.get_width() / (f32) window.get_height());
		set_window_size(glm::vec2(window.get_width(), window.get_height()));
	}
    
	void Camera::update() {
        if (dirty.load()) {
//           std::cout << "New Window Size: " << window_size << std::endl;
            projection = glm::ortho(0.0f, window_size.x, 0.0f, window_size.y, -1000.f, 1000.0f);
            // projection = glm::perspectiveFov(90.0f, window_size.x, window_size.y, -1.0f, 1.0f);
            // projection = glm::infinitePerspective(90.0f, aspect_ratio, -1.0f);
//             std::cout << "Persepctive: \n" << this->projection << std::endl;
            
            transform = glm::mat4(1);
            transform = glm::translate(transform, position);
			transform = glm::scale(transform, glm::vec3(zoom, 1));
            transform = glm::rotate(transform, theta, glm::vec3(0, 0, 1));
            
 //           std::cout << "Transform: \n" << transform << std::endl;
            
            dirty.store(false);
        }
    }
}
