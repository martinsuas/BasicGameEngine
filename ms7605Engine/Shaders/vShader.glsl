#version 430
// GL Vertex Shader
// Basic 2D

layout (location = 0) in vec3 position;
// 1                  2  3    4
// 1.Specifies a vertex attribute index e.g., glVertexAtrribPointer(0..)
// 2. Input data only
// 3. data type
// 4. variable name - in this case must be position

layout( location = 1) uniform mat4 matrix;
layout( location = 2) uniform vec2 textureCoord;
layout( location = 3) uniform int flip;
// Blended variable
out vec2 color;
out vec2 texCoord;

void main() {
	gl_Position = matrix * vec4(position, 1) ;
//  1                   2
//  1. A pre-defined shader variabler, a 4-component vector that:
//      * defines the location of the vertex in the window
//      * Should be set before the sahder ends.
//  2. position is the first 3 componets.
	texCoord = textureCoord;
	if (flip != 0) {
		//nada
	}
	color = position.xy;
}