#version 420 core
out vec4 FragColor;
  

uniform sampler2D txtx;
in vec2 out_coords;

void main()
{

	vec4 texColor = texture(txtx, out_coords);
    if(texColor.a < 1.0)
        discard;

    FragColor = texColor;

} 