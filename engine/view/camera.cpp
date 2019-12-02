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
            projection = glm::ortho(0.0f, window_size.x, 0.0f, window_size.y, -1000.f, 1000.0f);
            
            transform = glm::mat4(1);
            transform = glm::translate(transform, position);
			transform = glm::scale(transform, glm::vec3(zoom, 1));
            transform = glm::rotate(transform, theta, glm::vec3(0, 0, 1));
            
            dirty.store(false);
        }
    }
}
