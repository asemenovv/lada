#version 330 core

out vec4 FragColor;

in vec2 v_TextCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TextCoord);
    FragColor = vec4(0.3f * u_Color.rgb + 0.7f * texColor.rgb, texColor.a);
}
