#include "color.hpp"

namespace gfx {
    OpaqueColor::OpaqueColor(f32 r, f32 g, f32 b, f32 a) {
        color_data = {r, g, b, a};
    }
    
    Color Color::White = Color(1.0, 1.0, 1.0);
    Color Color::Red = Color(1.0, 0.0, 0.0);
    Color Color::Blue = Color(0.0, 0.0, 1.0);
    Color Color::Green = Color(0.0, 1.0, 0.0);
    Color Color::Black = Color(0.0, 0.0, 0.0);
    
    Color::Color(f32 r, f32 g, f32 b) {
        color_data = {r, g, b};
    }
    
    OpaqueColor Color::with_opacity(f32 alpha) {
        return OpaqueColor(r, g, b, alpha);
    }
    
}
