#ifndef ORTHO_CAMERA_HPP_
#define ORTHO_CAMERA_HPP_

#include "common.hpp"
#include <glm/glm.hpp>
#include "utils/singleton.hpp"

namespace view {
#ifdef SINGLE_CAMERA
	class OrthoCamera : public util::Singleton<OrthoCamera> {
#else
	class OrthoCamera {
#endif
		public:
			OrthoCamera();
			
			void update_view();

			inline const glm::mat4& get_projection() const;
			
			inline void set_position(const glm::vec2& position);

			inline glm::vec2 get_position() const;

			inline void set_rotation(f32 theta);

			inline f32 get_rotation() const;

			inline void set_size(u32 width, u32 height);

		private:
			/// the center of the camera
			glm::vec2 position;	
			/// the "origin" of the camera. I.E. the bottom left of the camera.
			glm::vec2 origin;
			/// the size of the orthographic view.
			glm::vec2 size;
			/// rototion of the camera in a clockwise rotation. In radians.
			/// Positive angles
			f32 theta;
			/// the viewing projection
			glm::mat4 projection;
	};

	inline void OrthoCamera::set_position(const glm::vec2& position) {
		this->position = position;
	}

	inline glm::vec2 OrthoCamera::get_position() const {
		return position;
	}

	inline void OrthoCamera::set_rotation(f32 theta) {
		this->theta = theta;
	}


	inline f32 OrthoCamera::get_rotation() const {
		return theta;
	}

	inline void OrthoCamera::set_size(u32 width, u32 height) {
		size = glm::ivec2(width, height);
	}
	
	inline const glm::mat4& OrthoCamera::get_projection() const {
		return projection;
	}

}

#endif
