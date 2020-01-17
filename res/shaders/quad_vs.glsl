#version 330 core

layout (location = 0) in vec3 quadPosition;
layout (location = 1) in vec2 size;
layout (location = 2) in vec4 texInfo;
layout (location = 3) in vec4 colorMask;
layout (location = 4) in float rotation;


out VS_OUT {
	vec4 texInfo;
	vec4 color_mask;
	vec2 size;
	float rotation;
} vs_out;

void main() {
    gl_Position = vec4(quadPosition, 1);

    vs_out.texInfo = texInfo;
    vs_out.color_mask = colorMask;
	vs_out.size = size;
	vs_out.rotation = rotation;
}

