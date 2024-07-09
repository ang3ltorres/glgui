#version 460 core

in GS_OUTPUT {
	vec3 color;
	vec2 texCoord;
} fs_in;

out vec4 color;

uniform sampler2D image;

void main()
{
	color = vec4(fs_in.color, 1.0) * texture(image, fs_in.texCoord);
}
