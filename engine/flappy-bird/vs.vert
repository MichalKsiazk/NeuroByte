#version 420 core
layout (location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_coords;

uniform mat4 modelMatrix;  
uniform mat4 cameraMatrix;


out vec2 out_coords;
void main()
{
    gl_Position = cameraMatrix * modelMatrix * vec4(in_position, 1.0);
	out_coords = in_coords;
}