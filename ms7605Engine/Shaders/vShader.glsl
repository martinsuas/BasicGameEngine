#version 430
// GL Vertex Shader
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normal;

uniform mat4 matrix;
uniform int flip;

// Blended variable
out vec2 color;
out vec2 texCoord;
void main()
{
	gl_Position = matrix * vec4(position, 1); 
	texCoord = textureCoord;
	if (flip == 0) {
		texCoord.x = -1 * texCoord.x;
	}
	color = position.xy;
}
