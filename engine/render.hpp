#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "common.hpp"

#include <glm/glm.hpp>

namespace entity {
	struct Entity;
}

namespace graphics {
	class Renderer {
		public:
			Renderer();

			void submit(entity::Entity* entity);

			void present();
		
			void clear();
		private:

			struct RenderInstanceData {
				u32 texture;
				glm::vec2 position;
				glm::vec2 size;
				glm::vec2 uv;
				glm::vec2 uv_size;
				glm::vec4 hue;
				f32 rotation;
			};

			std::unordered_map<u32, RenderInstanceData> objects;
	};
}

#endif
