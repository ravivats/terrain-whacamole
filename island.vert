#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;
out float height;
  

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

uniform float islandmult = 0.01;
uniform float phase = 0.01;
uniform float wamp = 0.01;
uniform float wint = 1.0;

uniform sampler2D ourTexture2;

void main()
{
	vec4 tex = texture(ourTexture2, texCoord);
	vec3 island = vec3(0.0, 0.0, (tex.x + tex.y + tex.z)/3) * islandmult;
	
    vec3 wave = vec3(0.0,0.0,sin(4.0 * (position.x * wint + phase)) + cos(4.0 * (position.y * wint+ phase))) * wamp;

	vec4 pos;

	if (island.z > 0)
		pos = vec4(position + island, 1.0f);
	else
		pos = vec4(position + wave, 1.0f);


	gl_Position = projection * view * transform * pos;
    TexCoord = vec2(texCoord.x, texCoord.y);
	height = island.z;
} 