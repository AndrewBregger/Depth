#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "common.hpp"
#include "utils/singleton.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const u32 WINDOW_WIDTH = 800;
const u32 WINDOW_HEIGHT = 800;

namespace win {
	/// Window abstraction.
	class Window : public utils::Singleton<Window> {
		public:
			// Window(const Config& config);

			/// Temporary constructor.
			Window();
			
			/// destructor
			~Window();
			
			/// makes this gl context current for the current thread.
			void make_current();
			
			/// unsets this context as current.
			void unset_context();

			/// creates the window
			/// title: the title of the window
			/// width: the width of the new window
			/// height: the height of the new window
			/// pos: the position to place the window
			/// fullscreen: true will make the window fullscreen,
			///				ignore the width and height parameters
			///				false will create a window the given width
			///				and height.
			void create_glwindow(const std::string& title, 
					u32 width, u32 height, const glm::ivec2& pos, bool fullscreen);
		
			/// get the glfw handle of the window.
			inline auto get_handle() const { return handle; }
			
			/// check if the screen is full screen or not.
			inline auto is_fullscreen() const { return fullscreen; }

			/// swaps the front and back buffers
			inline void swapbuffers() { glfwSwapBuffers(handle); }
		
			/// returns the title
			inline const std::string& get_title() { return title; }
		
			/// returns the width of the window
			inline auto get_width() const { return width; }

			/// returns the height of the window
			inline auto get_height() const { return height; }
			
			/// returns the current position of the window.
			inline const glm::ivec2& get_position() const { return position; }
		private:
			/// the title of the window
			std::string title;
			/// Window width
			u32 width{0};
			/// Window height
			u32 height{0};
			/// the position of the window
			glm::ivec2 position{0, 0};
			/// boolean representing if the window is full screen or not.
			bool fullscreen{false};
			/// GLFW window handle
			GLFWwindow* handle{nullptr};
			/// GLFW monitor handle
			GLFWmonitor* monitor{nullptr};

			static bool glfw_initiated;
	};
}

#endif
