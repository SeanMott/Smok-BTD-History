
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D Sprite;
uniform vec3 Color;

void main()
{
    color = vec4(Color, 1.0) * texture(Sprite, TexCoords);
}