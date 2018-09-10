#version 420 core

out vec4 FragColor;

uniform vec3 customColor;

uniform sampler2D txtx;
in vec2 out_coords;

void main()
{

	vec4 texColor = texture(txtx, out_coords);
    if(texColor.a < 0.8)
        discard;
	if(texColor.r > 0.3 && texColor.g > 0.3 && texColor.b < 0.55)
	{
		texColor = (texColor * 1.3f) * vec4(customColor,1.0f);
	}

    FragColor = texColor;

} 