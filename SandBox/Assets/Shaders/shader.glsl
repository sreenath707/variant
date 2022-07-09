#type vertex
#version 330 core
layout(location=0) in vec3 a_position;
layout(location=1) in vec2 a_textureCoords;
layout(location=2) in vec4 a_color;

uniform mat4 u_viewProjection;


out vec2 v_texCords;
out vec4 f_color;

void main()
{
	v_texCords = a_textureCoords;
	f_color = a_color;
	gl_Position =  u_viewProjection * vec4(a_position,1.0);
}


#type fragment
#version 330 core
layout (location=0) out vec4 color;

in vec2 v_texCords;
in vec4 f_color;

uniform sampler2D u_texture;
void main()
{
	color =  f_color;
}


