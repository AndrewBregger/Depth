#ifndef EVENTS_HPP_
#define EVENTS_HPP_

#include "input.hpp"
#include "common.hpp"
#include "listener.hpp"

#include <unordered_map>
#include <functional>

namespace win {
	class Window;
}

namespace event {
	enum EventType {
		Startup,
		Shutdown,
		OnRender,
		KeyEvent,
		ScrollEvent,
		MouseMoveEvent,
		MouseButtonEvent,
		CharEvent,
	};

	class EventManager : public utils::Singleton<EventManager> {
		public:
			typedef std::function<void(Listener*)> EventCallback;

			EventManager(win::Window* window);

			void process_events();
			
			void process_callbacks();

			void set_event_type(EventType type);

			void register_callback(EventType event, Listener* listern, EventCallback&& callback);

		private:
			
			void init();

			Input input;
			win::Window* window;
			EventType current_event;

			std::unordered_map<EventType, std::vector<std::pair<Listener*, EventCallback>>> callbacks;
	};
}

#endif
