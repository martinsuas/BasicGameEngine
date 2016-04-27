#version 430

in vec2 color;
in vec2 texCoord;
uniform sampler2D myTexture;

void main() {

	vec4 texColor = texture(myTexture, color);
	if(texColor.a < 0.5)
		discard;
	gl_FragColor = texColor;
}
// gl_FragColor shoudl be set before shader ends