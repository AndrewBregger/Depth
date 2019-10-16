#include "events.hpp"
#include "window.hpp"

#include <GLFW/glfw3.h>

namespace event {
	void mouse_button_callback(GLFWwindow *, int button, int action, int mods) {
		auto input = Input::get();
		
		MouseButton ibutton = Input::from_glfw_button(button);

		Input::MouseState& state = input->mouse_state;
		
		state.press_location = Input::mouse_position();

		switch(action) {
			case GLFW_RELEASE:
				state.pressed = false;
				break;
			case GLFW_PRESS:
				state.pressed = true;
				break;
			default:
				assert(false);
		}
	}

	void cursor_position_callback(GLFWwindow *, double xpos, double ypos) {
		auto input = Input::get();
		input->mouse_pos = glm::dvec2(xpos,  ypos);
	}

	void cursor_enter_callback(GLFWwindow *, int entered) {
		auto input = Input::get();
		LOG_INFO("Cursor {} the window", entered == 1 ? "true" : "false");
	}

	void scroll_callback(GLFWwindow *, double xoffset, double yoffset) {
		auto input = Input::get();
		input->mouse_scroll_x = xoffset;
		input->mouse_scroll_y = yoffset;
	}

	void key_callback(GLFWwindow *, int key, int scancode, int action, int mods) {
		auto input = Input::get();

		auto ikey = Input::from_glfw_button(key);

		Input::KeyState& state = input->key_state[ikey];

		switch(action) {
			case GLFW_RELEASE:
				state.just_released = true;
				state.pressed = false;
				state.repeat = false;
				break;
			case GLFW_PRESS:
				state.just_released = true;
				state.pressed = true;
				state.repeat = true;
				break;
			case GLFW_REPEAT:
				state.just_released = false;
				state.pressed = true;
				state.repeat = true;
				break;
			default:
				assert(false);
		}
	}

	void char_callback(GLFWwindow *, unsigned int codepoint) {
		auto input = Input::get();
		input->input_character = std::optional<u32>(codepoint);
	}

	EventManager::EventManager(win::Window* window) : input(), window(window) {
		init();
	}

	void EventManager::process_events() {
		glfwPollEvents();
	}

	void EventManager::process_callbacks() {
		auto iter = callbacks.find(current_event);
		if(iter != callbacks.end()) {
			for(const auto& callback : iter->second) {
				callback.second(callback.first);
			}
		}
	}
	
	void EventManager::init() {
		glfwSetKeyCallback(window->get_handle(), key_callback);
		glfwSetCharCallback(window->get_handle(), char_callback);
		glfwSetMouseButtonCallback(window->get_handle(), mouse_button_callback);
		glfwSetCursorPosCallback(window->get_handle(), cursor_position_callback);
		glfwSetCursorEnterCallback(window->get_handle(), cursor_enter_callback);
		glfwSetScrollCallback(window->get_handle(), scroll_callback);
	}

	void EventManager::set_event_type(EventType type) {
		current_event = type;
	}

	void EventManager::register_callback(EventType event, Listener* listener,
			EventCallback&& callback) {
		auto event_callbacks = callbacks.find(event);

		if(event_callbacks == callbacks.end()) {
			auto inserted = callbacks.emplace(event, std::vector<std::pair<Listener*, EventCallback>>());
			inserted.first->second.push_back(std::make_pair(listener, std::move(callback)));
		}
		else {
			event_callbacks->second.push_back(std::make_pair(listener, std::move(callback)));
		}

	}
}
