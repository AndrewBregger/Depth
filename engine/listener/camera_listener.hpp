#ifndef CAMERA_LISTENER_HPP_
#define CAMERA_LISTENER_HPP_

#include "camera.hpp"
#include "listener.hpp"

namespace listener {
	struct CameraListener : public Listener {
		view::Camera* camera;

		CameraListener(view::Camera* camera) : camera(camera) {}
	};
}

#endif
