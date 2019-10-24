#ifndef CAMERA_LISTENER_HPP_
#define CAMERA_LISTENER_HPP_

#include "ortho_camera.hpp"
#include "listener.hpp"

namespace listener {
	struct CameraListener : public Listener {
		view::OrthoCamera* camera;

		CameraListener(view::OrthoCamera* camera) : camera(camera) {}
	};
}

#endif
