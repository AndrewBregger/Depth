#include "input.hpp"

#include <GLFW/glfw3.h>



namespace event {
	static GLFWKey glfw_keys[NUM_KEYS] = {
#define KEY_MAP(Key, GLFW_KEY) GLFW_KEY,
		KEY_MAPPING
#undef KEY_MAP
	};
    
	bool Input::is_key_pressed(Key key) {
		return Input::get()->key_state[key].pressed;
	}
    
	bool Input::is_key_released(Key key) {
		return Input::get()->key_state[key].just_released;
	}
	
	bool Input::is_ctrl_pressed() {
		return Input::is_key_pressed(Key_Right_Control) ||
            Input::is_key_pressed(Key_Left_Control);
	}
    
	bool Input::is_alt_pressed() {
		return Input::is_key_pressed(Key_Right_Alt) ||
            Input::is_key_pressed(Key_Left_Alt);
	}
    
	bool Input::is_super_pressed() {
		return Input::is_key_pressed(Key_Right_Super) ||
            Input::is_key_pressed(Key_Left_Super);
	}
	
	bool Input::is_shift_pressed() {
		return Input::is_key_pressed(Key_Right_Shift) ||
            Input::is_key_pressed(Key_Left_Shift);
	}
    
	bool Input::is_enter_pressed() {
		return Input::is_key_pressed(Key_Enter);
	}
    
	f64 Input::scroll_x() {
		return Input::get()->mouse_scroll_x;
	}
    
	f64 Input::scroll_y() {
		return Input::get()->mouse_scroll_y;
	}
    
	glm::dvec2 Input::mouse_position() {
		return Input::get()->mouse_pos;
	}
    
	bool Input::is_mouse_pressed() {
		return Input::get()->mouse_state.pressed;
	}
    
	std::optional<glm::vec2> Input::mouse_press_location() {
		if(Input::is_mouse_pressed()) {
			return std::optional<glm::ivec2>();
		}
		else {
			return std::optional<glm::ivec2>(Input::get()->
                                             mouse_state.press_location);
		}
	}


	f64  Input::get_delta() {
		return Input::get()->delta_time;
	}

	void Input::set_delta(f64 delta) {
		Input::get()->delta_time = delta;
	}
    
    void Input::new_frame() {
        Input::get()->reset();
    }
    
    void Input::reset() {
        mouse_state = {};
        mouse_scroll_x = 0.0;
        mouse_scroll_y = 0.0;
        input_character = std::optional<u32>();
        std::memset(key_state, 0, sizeof(KeyState) * NUM_KEYS);
    }
    
    
	std::optional<u32> Input::character_input() {
		return Input::get()->input_character;
	}
    
    
	Key Input::from_glfw_key(GLFWKey glfw_key) {
		switch(glfw_key) {
#define KEY_MAP(Key, GLFW_KEY) case GLFW_KEY: return Key;
			KEY_MAPPING
#undef KEY_MAP
                default:
            assert(false);
		}
	}
	GLFWKey Input::from_key(Key key) {
		assert(key < NUM_KEYS);
		return glfw_keys[key];
	}
    
	glm::ivec2 Input::window_resize() { 
		return Input::get()->window_size;
	}
    
	glm::ivec2 Input::framebuffer_resize() { 
		return Input::get()->framebuffer_size;
	}
}
