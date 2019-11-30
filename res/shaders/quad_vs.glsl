#version 330 core

layout (location = 0) in vec4 quadInfo;
layout (location = 1) in vec4 texInfo;
layout (location = 2) in vec4 colorMask;
layout (location = 3) in float rotation;


out VS_OUT {
	vec4 texInfo;
	vec4 color_mask;
	vec2 size;
	float rotation;
} vs_out;


void main() {
    gl_Position = vec4(quadInfo.xy, 0, 1);

    vs_out.texInfo = texInfo;
    vs_out.color_mask = colorMask;
	vs_out.size = quadInfo.zw;
	vs_out.rotation = rotation;
}

