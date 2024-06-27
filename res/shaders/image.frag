#version 460 core

in GS_OUTPUT {
	vec3 color;
	vec2 texCoord;
} fs_in;

out vec4 color;

uniform sampler2D image;

void main()
{
	int r = int(texture(image, fs_in.texCoord).x * 255.0f);
	int g = int(texture(image, fs_in.texCoord).y * 255.0f);
	int b = int(texture(image, fs_in.texCoord).z * 255.0f);

	if (r > 170 && b > 170 && g > 170)
		color = vec4(0.0, 1.0, 0.0, 1.0);
	else
		color = vec4(fs_in.color, 1.0) * texture(image, fs_in.texCoord);

	// color = vec4(fs_in.color, 1.0);

}
