#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

// the input position is the top left of the quad we want.

in VS_OUT {
	vec4 texInfo;
	vec4 color_mask;
	vec2 size;
	float rotation;
} gs_in[];

out GS_OUT {
	vec2 tex;
	vec4 color_mask;
} gs_out;

uniform mat4 perspective;
uniform mat4 view;

void build_quad(vec4 position) {
	vec2 baseCoords = gs_in[0].texInfo.xy;
	vec2 sizeCoords = gs_in[0].texInfo.zw;
	vec2 size = gs_in[0].size;

	mat4 mvp = perspective * view;

	gl_Position = mvp * (position + vec4(size, 0, 0));
	gs_out.tex = baseCoords + sizeCoords;
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();

	gl_Position = mvp * (position + vec4(size.x, 0, 0, 0));
	gs_out.tex = baseCoords + vec2(sizeCoords.x, 0);
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();

	gl_Position = mvp * (position + vec4(0, size.y, 0, 0));
	gs_out.tex = baseCoords + vec2(0, sizeCoords.y);
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();

	gl_Position = mvp * position;
	gs_out.tex = baseCoords;
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();
}

mat4 rotationMatrix(vec3 axis, float angle) {
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

vec3 rotate(vec3 v, vec3 axis, float angle) {
	mat4 m = rotationMatrix(axis, angle);
	return (m * vec4(v, 1.0)).xyz;
}

void build_quad_from_center(vec4 center) {
	vec2 baseCoords = gs_in[0].texInfo.xy;
	vec2 sizeCoords = gs_in[0].texInfo.zw;
	vec2 size = gs_in[0].size;

	mat4 mvp = perspective * view * rotationMatrix(vec3(0, 0, 1), gs_in[0].rotation);

	vec4 position = center - vec4(size.xy / 2, 0.0, 0.0);

	gl_Position = mvp * (position + vec4(size, 0, 0));
	gs_out.tex = baseCoords + sizeCoords;
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();

	gl_Position = mvp * (position + vec4(size.x, 0, 0, 0));
	gs_out.tex = baseCoords + vec2(sizeCoords.x, 0);
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();

	gl_Position = mvp * (position + vec4(0, size.y, 0, 0));
	gs_out.tex = baseCoords + vec2(0, sizeCoords.y);
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();

	gl_Position = mvp * position;
	gs_out.tex = baseCoords;
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();
}


void main() {
	build_quad(gl_in[0].gl_Position);
	EndPrimitive();
}
