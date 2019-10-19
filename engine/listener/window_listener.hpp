#ifndef WINDOW_LISTENER_HPP_
#define WINDOW_LISTENER_HPP_

#include "window.hpp"
#include "listener.hpp"


namespace listener {
	struct WindowListener : public Listener {
		win::Window* window;
		WindowListener(win::Window* window) : window(window) {}
	};
}

#endif
