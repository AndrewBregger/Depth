#ifndef INPUT_HPP_
#define INPUT_HPP_
#include "common.hpp"
#include "utils/singleton.hpp"

#include <glm/glm.hpp>
#include <optional>

#define KEY_MAPPING \
		KEY_MAP(Key_Unknown, GLFW_KEY_UNKNOWN) \
		KEY_MAP(Key_Space, GLFW_KEY_SPACE) \
		KEY_MAP(Key_Apostrophe, GLFW_KEY_APOSTROPHE) \
		KEY_MAP(Key_Comma, GLFW_KEY_COMMA) \
		KEY_MAP(Key_Minus, GLFW_KEY_MINUS) \
		KEY_MAP(Key_Period, GLFW_KEY_PERIOD) \
		KEY_MAP(Key_Slash, GLFW_KEY_SLASH) \
		KEY_MAP(Key_0, GLFW_KEY_0) \
		KEY_MAP(Key_1, GLFW_KEY_1) \
		KEY_MAP(Key_2, GLFW_KEY_2) \
		KEY_MAP(Key_3, GLFW_KEY_3) \
		KEY_MAP(Key_4, GLFW_KEY_4) \
		KEY_MAP(Key_5, GLFW_KEY_5) \
		KEY_MAP(Key_6, GLFW_KEY_6) \
		KEY_MAP(Key_7, GLFW_KEY_7) \
		KEY_MAP(Key_8, GLFW_KEY_8) \
		KEY_MAP(Key_9, GLFW_KEY_9) \
		KEY_MAP(Key_SemiColon, GLFW_KEY_SEMICOLON) \
		KEY_MAP(Key_Equal, GLFW_KEY_EQUAL) \
		KEY_MAP(Key_A, GLFW_KEY_A) \
		KEY_MAP(Key_B, GLFW_KEY_B) \
		KEY_MAP(Key_C, GLFW_KEY_C) \
		KEY_MAP(Key_D, GLFW_KEY_D) \
		KEY_MAP(Key_E, GLFW_KEY_E) \
		KEY_MAP(Key_F, GLFW_KEY_F) \
		KEY_MAP(Key_G, GLFW_KEY_G) \
		KEY_MAP(Key_H, GLFW_KEY_H) \
		KEY_MAP(Key_I, GLFW_KEY_I) \
		KEY_MAP(Key_J, GLFW_KEY_J) \
		KEY_MAP(Key_K, GLFW_KEY_K) \
		KEY_MAP(Key_L, GLFW_KEY_L) \
		KEY_MAP(Key_M, GLFW_KEY_M) \
		KEY_MAP(Key_N, GLFW_KEY_N) \
		KEY_MAP(Key_O, GLFW_KEY_O) \
		KEY_MAP(Key_P, GLFW_KEY_P) \
		KEY_MAP(Key_Q, GLFW_KEY_Q) \
		KEY_MAP(Key_R, GLFW_KEY_R) \
		KEY_MAP(Key_S, GLFW_KEY_S) \
		KEY_MAP(Key_T, GLFW_KEY_T) \
		KEY_MAP(Key_U, GLFW_KEY_U) \
		KEY_MAP(Key_V, GLFW_KEY_V) \
		KEY_MAP(Key_W, GLFW_KEY_W) \
		KEY_MAP(Key_X, GLFW_KEY_X) \
		KEY_MAP(Key_Y, GLFW_KEY_Y) \
		KEY_MAP(Key_Z, GLFW_KEY_Z) \
		KEY_MAP(Key_Left_Bracket, GLFW_KEY_LEFT_BRACKET) \
		KEY_MAP(Key_BackSlash, GLFW_KEY_BACKSLASH) \
		KEY_MAP(Key_Right_Bracket, GLFW_KEY_RIGHT_BRACKET) \
		KEY_MAP(Key_Accent, GLFW_KEY_GRAVE_ACCENT) \
		KEY_MAP(Key_World_1, GLFW_KEY_WORLD_1) \
		KEY_MAP(Key_World_2, GLFW_KEY_WORLD_2) \
		KEY_MAP(Key_ESC, GLFW_KEY_ESCAPE) \
		KEY_MAP(Key_Enter, GLFW_KEY_ENTER) \
		KEY_MAP(Key_Tab, GLFW_KEY_TAB) \
		KEY_MAP(Key_BackSpace, GLFW_KEY_BACKSPACE) \
		KEY_MAP(Key_Insert, GLFW_KEY_INSERT) \
		KEY_MAP(Key_Delete, GLFW_KEY_DELETE) \
		KEY_MAP(Key_Right, GLFW_KEY_RIGHT) \
		KEY_MAP(Key_Left, GLFW_KEY_LEFT) \
		KEY_MAP(Key_Down, GLFW_KEY_DOWN) \
		KEY_MAP(Key_Up, GLFW_KEY_UP) \
		KEY_MAP(Key_Page_Up, GLFW_KEY_PAGE_UP) \
		KEY_MAP(Key_Page_Down, GLFW_KEY_PAGE_DOWN) \
		KEY_MAP(Key_Home, GLFW_KEY_HOME) \
		KEY_MAP(Key_End, GLFW_KEY_END) \
		KEY_MAP(Key_Caps_Lock, GLFW_KEY_CAPS_LOCK) \
		KEY_MAP(Key_Scroll_Lock, GLFW_KEY_SCROLL_LOCK) \
		KEY_MAP(Key_Num_Lock, GLFW_KEY_NUM_LOCK) \
		KEY_MAP(Key_Print_Screen, GLFW_KEY_PRINT_SCREEN) \
		KEY_MAP(Key_Pause, GLFW_KEY_PAUSE) \
		KEY_MAP(Key_F1, GLFW_KEY_F1) \
		KEY_MAP(Key_F2, GLFW_KEY_F2) \
		KEY_MAP(Key_F3, GLFW_KEY_F3) \
		KEY_MAP(Key_F4, GLFW_KEY_F4) \
		KEY_MAP(Key_F5, GLFW_KEY_F5) \
		KEY_MAP(Key_F6, GLFW_KEY_F6) \
		KEY_MAP(Key_F7, GLFW_KEY_F7) \
		KEY_MAP(Key_F8, GLFW_KEY_F8) \
		KEY_MAP(Key_F9, GLFW_KEY_F9) \
		KEY_MAP(Key_F10, GLFW_KEY_F10) \
		KEY_MAP(Key_F11, GLFW_KEY_F11) \
		KEY_MAP(Key_F12, GLFW_KEY_F12) \
		KEY_MAP(Key_F13, GLFW_KEY_F13) \
		KEY_MAP(Key_F14, GLFW_KEY_F14) \
		KEY_MAP(Key_F15, GLFW_KEY_F15) \
		KEY_MAP(Key_F16, GLFW_KEY_F16) \
		KEY_MAP(Key_F17, GLFW_KEY_F17) \
		KEY_MAP(Key_F18, GLFW_KEY_F18) \
		KEY_MAP(Key_F19, GLFW_KEY_F19) \
		KEY_MAP(Key_F20, GLFW_KEY_F20) \
		KEY_MAP(Key_F21, GLFW_KEY_F21) \
		KEY_MAP(Key_F22, GLFW_KEY_F22) \
		KEY_MAP(Key_F23, GLFW_KEY_F23) \
		KEY_MAP(Key_F24, GLFW_KEY_F24) \
		KEY_MAP(Key_F25, GLFW_KEY_F25) \
		KEY_MAP(Key_K0, GLFW_KEY_KP_0) \
		KEY_MAP(Key_K1, GLFW_KEY_KP_1) \
		KEY_MAP(Key_K2, GLFW_KEY_KP_2) \
		KEY_MAP(Key_K3, GLFW_KEY_KP_3) \
		KEY_MAP(Key_K4, GLFW_KEY_KP_4) \
		KEY_MAP(Key_K5, GLFW_KEY_KP_5) \
		KEY_MAP(Key_K6, GLFW_KEY_KP_6) \
		KEY_MAP(Key_K7, GLFW_KEY_KP_7) \
		KEY_MAP(Key_K8, GLFW_KEY_KP_8) \
		KEY_MAP(Key_K9, GLFW_KEY_KP_9) \
		KEY_MAP(Key_KDecimal, GLFW_KEY_KP_DECIMAL) \
		KEY_MAP(Key_KDivide, GLFW_KEY_KP_DIVIDE) \
		KEY_MAP(Key_KMultiply, GLFW_KEY_KP_MULTIPLY) \
		KEY_MAP(Key_KSubtract, GLFW_KEY_KP_SUBTRACT) \
		KEY_MAP(Key_KAdd, GLFW_KEY_KP_ADD) \
		KEY_MAP(Key_KEnter, GLFW_KEY_KP_ENTER) \
		KEY_MAP(Key_KEQ, GLFW_KEY_KP_EQUAL) \
		KEY_MAP(Key_Left_Shift, GLFW_KEY_LEFT_SHIFT) \
		KEY_MAP(Key_Left_Control, GLFW_KEY_LEFT_CONTROL) \
		KEY_MAP(Key_Left_Alt, GLFW_KEY_LEFT_ALT) \
		KEY_MAP(Key_Left_Super, GLFW_KEY_LEFT_SUPER) \
		KEY_MAP(Key_Right_Shift, GLFW_KEY_RIGHT_SHIFT) \
		KEY_MAP(Key_Right_Control, GLFW_KEY_RIGHT_CONTROL) \
		KEY_MAP(Key_Right_Alt, GLFW_KEY_RIGHT_ALT) \
		KEY_MAP(Key_Right_Super, GLFW_KEY_RIGHT_SUPER) \
		KEY_MAP(Key_Menu, GLFW_KEY_MENU)

namespace event {
	enum Key : i8 {
#define KEY_MAP(Key, ...) Key,
		KEY_MAPPING
#undef KEY_MAP
		NUM_KEYS
	};

	typedef i16 GLFWKey;
	typedef u16 GLFWMouseButton;

	enum MouseButton {
		MouseButton1,
		MouseButton2,
		MouseButton3,
		MouseButton4,
		MouseButton6,
		MouseButton7,
		MouseButton8,
		MouseButtonLast = MouseButton8,
		MouseButtonLeft = MouseButton1,
		MouseButtonRight = MouseButton2,
		MouseButtonMiddle = MouseButton3,
	};

	class EventManager;

	struct Input : public utils::Singleton<Input> {
		struct KeyState {
			bool pressed;
			bool just_released;
			bool repeat;
		};

		struct MouseState {
			bool pressed;
			MouseButton button;
			glm::dvec2 press_location;
		};

		Input() = default;

		
		/// check if a key was just pressed or is continually pressed
		static bool is_key_pressed(Key key);
		
		/// Check if a key was just released
		static bool is_key_released(Key key);
		
		/// helper function for checking explicity for control key
		static bool is_ctrl_pressed();

		/// helper function for checking explicity for alt key
		static bool is_alt_pressed();

		/// helper function for checking explicity for windows/command
		static bool is_super_pressed();
		
		/// helper function for checking explicity for shift key
		static bool is_shift_pressed();

		/// helper function for checking explicity for enter key
		static bool is_enter_pressed();

		static f64 scroll_x();

		static f64 scroll_y();

		static glm::dvec2 mouse_position();

		static bool is_mouse_pressed();
		static std::optional<glm::vec2> mouse_press_location();

		static std::optional<u32> character_input();
		
		/// Returns the key from the given glfw key
		static Key from_glfw_key(GLFWKey glfw_key);

		/// Returns the glfw key from the given key
		static GLFWKey from_key(Key key);

		/// Returns the MouseButton from the given glfw mouse button
		inline static MouseButton from_glfw_button(GLFWMouseButton glfw_button) {
			return static_cast<MouseButton>(glfw_button);
		}

		/// Returns the glfw mouse
		inline static GLFWMouseButton from_button(MouseButton button) {
			return static_cast<GLFWMouseButton>(button);
		}
		

			KeyState key_state[NUM_KEYS];
			std::optional<u32> input_character;
			f64 mouse_scroll_x{0.0};
			f64 mouse_scroll_y{0.0};
			glm::dvec2 mouse_pos{0, 0};
			MouseState mouse_state;

		//friend class EventManager;
	};
}

#endif
