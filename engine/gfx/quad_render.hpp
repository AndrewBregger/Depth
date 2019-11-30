#ifndef QUAD_RENDERER_HPP_
#define QUAD_RENDERER_HPP_

#include "common.hpp"
#include "render.hpp"
#include "shader.hpp"

namespace gfx {
    //layout (location = 0) in vec4 quadInfo;
    //layout (location = 1) in vec4 texInfo;
    //layout (location = 2) in vec4 colorMask;
    //layout (location = 3) in float rotation;
    
    class QuadRenderer : public Renderer {
        public:
        QuadRenderer(view::Camera* camera);
        
		virtual void init();

        private:
        
        /// Shader uniform location
		/// location of perspective matrix uniform
        u32 perspective;

		/// location of view matrix uniform
        u32 view;

		/// location of texture sampler
		u32 texture;
        
   };
}

#endif
