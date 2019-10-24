#include "ortho_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace view {
	OrthoCamera::OrthoCamera() = default;


	void OrthoCamera::update_view() {
		origin = glm::vec2(
					position.x - size.x / 2,
					position.y - size.y / 2
				);
		
		// I wonder if the left and top should be offset by the origin of the 
		// view.
		projection = glm::ortho(origin.x, size.x, origin.y, size.y, -1.0f, 1.0f);
	}
}
