#version 430

in vec2 color;
in vec2 texCoord;
uniform sampler2D myTexture;

void main() {

	vec4 texColor = texture(myTexture, texCoord);

	if(texColor.a < 0.5)
		discard;

	vec4 sim_color = vec4(color.x, color.y, 0, 0);
	gl_FragColor =  texColor;
}