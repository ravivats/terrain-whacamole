#version 330 core
in vec2 TexCoord;
in float height;

out vec4 color;

// Texture samplers
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform sampler2D ourTexture3;
uniform sampler2D ourTexture4;

void main()
{

	if (height > 0.075)
		color = mix(texture(ourTexture4, TexCoord), texture(ourTexture2, TexCoord),0.5);
	
	else if (height > 0.011 && height <1)
		color = mix(texture(ourTexture3, TexCoord), texture(ourTexture2, TexCoord), 0.5);

	
	else
		color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.1);
	
	
}
