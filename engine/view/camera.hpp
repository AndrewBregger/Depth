#ifndef ORTHO_CAMERA_HPP_
#define ORTHO_CAMERA_HPP_

#include "common.hpp"
#include "utils/singleton.hpp"

#include <atomic>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace win {
	class Window;
}

namespace view {
#ifdef SINGLE_CAMERA
	class Camera : public utils::Singleton<Camera> {
#else
        class Camera {
#endif
            public:
            Camera(const win::Window& window);
            
            void update();
            
            inline const glm::mat4& get_projection() const;
            
            inline const glm::mat4& get_transform() const;

            inline const glm::vec2& get_zoom() const;
            
            inline void set_position(const glm::vec3& position);
            
            inline glm::vec3 get_position() const;
            
            inline void set_aspect_ratio(f32 ratio);
            
            inline f32 get_aspect_ratio() const;
            
            inline void set_window_size(const glm::vec2& size);
            
            inline void set_rotation(f32 theta);

			inline void set_zoom(f32 x, f32 y);
            
            inline f32 get_rotation() const;
            
            inline bool should_update() const { return dirty; }
            
            private:
            /// the center of the camera
            glm::vec3 position;	
            /// the aspect ratio the camera
            f32 aspect_ratio;
            /// the window size;
            glm::vec2 window_size;
            /// rototion of the camera in a clockwise rotation. In degrees.
            f32 theta;
            /// the viewing projection
            glm::mat4 projection;
            /// the tranformation matrix
            glm::mat4 transform;
			/// camera zoom
			glm::vec2 zoom;
            
            std::atomic_bool dirty;
            
        };
        
        inline void Camera::set_position(const glm::vec3& position) {
            this->position = position;
            dirty.store(true);
        }
        
        inline glm::vec3 Camera::get_position() const {
            return position;
        }

		inline const glm::vec2& Camera::get_zoom() const {
			return zoom;
		}
        
        inline void Camera::set_rotation(f32 theta) {
            this->theta = theta;
            dirty.store(true);
        }

		inline void Camera::set_zoom(f32 x, f32 y) {
			zoom = glm::vec2(x, y);	
			dirty.store(true);
		}

        inline f32 Camera::get_rotation() const {
            return theta;
        }
        
        inline void Camera::set_aspect_ratio(f32 ratio) {
            aspect_ratio = ratio;
            dirty.store(true);
        }
        
        inline f32 Camera::get_aspect_ratio() const {
            return aspect_ratio;
        }
        
        inline void Camera::set_window_size(const glm::vec2& size) {
            window_size = size;
            dirty.store(true);
        }
        
        inline const glm::mat4& Camera::get_projection() const {
            return projection;
        }
        
        inline const glm::mat4& Camera::get_transform() const {
            return transform;
        }
    }
    
#endif
    
