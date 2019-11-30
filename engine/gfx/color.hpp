#ifndef COLOR_HPP_
#define COLOR_HPP_

#include "common.hpp"
#include <glm/glm.hpp>

namespace gfx {
    struct OpaqueColor {
        OpaqueColor(f32 r, f32 g, f32 b, f32 a);
        
        union {
            glm::vec4 color_data;
            struct {
                f32 r, g, b, a;
            };
        };
    };
    
    struct Color {
        static Color White;
        static Color Red;
        static Color Blue;
        static Color Green;
        static Color Black;
        // @Todo: Add more colors.
        // static Color  = Color(1.0, 1.0, 1.0);
        // static Color White = Color(1.0, 1.0, 1.0);
        
        Color(f32 r = 1.0, f32 g = 1.0, f32 b = 1.0);
        
        union {
            glm::vec3 color_data;
            struct {
                f32 r, g, b;
            };
        };
        
        OpaqueColor with_opacity(f32 alpha);
    };
}

#endif
