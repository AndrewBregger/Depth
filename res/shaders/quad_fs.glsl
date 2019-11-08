#version 330 core

uniform sampler2D tex;
uniform mat4 perspective;
uniform mat4 view;

in GS_OUT {
	vec2 tex;
	vec4 color_mask;
} gs_in;

out vec4 color;

void main() {
    color = texture(tex, gs_in.tex) * gs_in.color_mask;
}
