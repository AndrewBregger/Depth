#ifndef EVENTS_HPP_
#define EVENTS_HPP_

#include "input.hpp"
#include "common.hpp"
#include "listener/listener.hpp"

#include <unordered_map>
#include <functional>
#include <vector>
#include <mutex>

struct GLFWwindow;

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
		WindowResizeEvent,
		FramebufferResizeEvent,
        NumEventTypes,
	};
    
	class EventManager : public utils::Singleton<EventManager> {
		public:
        typedef std::function<void(Listener*)> EventCallback;
        
        EventManager(win::Window* window);
        
        void process_events();
        
        void process_callbacks();
        
        void set_event_type(EventType type);
        
        void register_callback(EventType event, Listener* listern, EventCallback&& callback);
        
        /// these method for the event propogation to handle non system events.
        /// These events are stateless.
        void push_event(EventType type);
        
        static void mouse_button_callback(GLFWwindow *, int button, int action, int mods);
        
        static void cursor_position_callback(GLFWwindow *, double xpos, double ypos);
        
        static void cursor_enter_callback(GLFWwindow *, int entered);
        
        static void scroll_callback(GLFWwindow *, double xoffset, double yoffset);
        
        static void key_callback(GLFWwindow *, int key, int scancode, int action, int mods);
        
        static void char_callback(GLFWwindow *, unsigned int codepoint);
        
        static void window_resize_callback(GLFWwindow *, int width, int height);
        
        static void framebuffer_resize_callback(GLFWwindow *, int width, int height);
        
		private:
        
        void init();
        
        
        Input input;
        win::Window* window;
        std::mutex event_queue_mutex;
        std::vector<EventType> event_queue;
        std::array<std::vector<std::pair<Listener*, EventCallback>>, EventType::NumEventTypes> callbacks;
	};
}

#endif
