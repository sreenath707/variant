
#type vertex
#version 330 core
layout(location=0) in vec3 a_position;

uniform vec4 u_color;
uniform mat4 u_viewProjection;
uniform mat4 u_transform;

out vec3 v_position;
out vec4 f_color;
void main()
{
	f_color = u_color;
	gl_Position = u_transform * u_viewProjection * vec4(a_position,1.0);
}


#type fragment
#version 330 core
layout (location=0) out vec4 color;

in vec4 f_color;
void main()
{
	color = f_color;
}


