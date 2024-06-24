#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUTPUT {
	vec3 color;
	vec2 texCoord;
} gs_in[];

out GS_OUTPUT {
	vec3 color;
	vec2 texCoord;
} gs_out;

void main()
{
	for (int i = 0; i < 3;  i++) {

		gl_Position = gl_in[i].gl_Position;
		gs_out.color = gs_in[i].color;
		gs_out.texCoord = gs_in[i].texCoord;

		EmitVertex();
	}

	EndPrimitive();
}