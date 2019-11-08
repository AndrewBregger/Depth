#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

// the input position is the top left of the quad we want.

in VS_OUT {
	vec4 texInfo;
	vec4 color_mask;
	vec2 size;
} gs_in[];

out GS_OUT {
	vec2 tex;
	vec4 color_mask;
} gs_out;

void build_quad(vec4 position) {
	vec2 baseCoords = gs_in[0].texInfo.xy;
	vec2 sizeCoords = gs_in[0].texInfo.zw;
	vec2 size = gs_in[0].size;

	gl_Position = position + vec4(size, 0, 0);
	gs_out.tex = baseCoords + sizeCoords;
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();

	gl_Position = position + vec4(size.x, 0, 0, 0);
	gs_out.tex = baseCoords + vec2(sizeCoords.x, 0);
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();

	gl_Position = position + vec4(0, size.y, 0, 0);
	gs_out.tex = baseCoords + vec2(0, sizeCoords.y);
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();

	gl_Position = position;
	gs_out.tex = baseCoords;
	gs_out.color_mask = gs_in[0].color_mask;
	EmitVertex();
}


void main() {
	build_quad(gl_in[0].gl_Position);
}
