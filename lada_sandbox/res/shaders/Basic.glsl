//shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;

out vec2 v_TextCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_TextCoord = texCoord;
}


//shader fragment
#version 330 core

out vec4 FragColor;

in vec2 v_TextCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TextCoord);
    FragColor = vec4(0.3f * u_Color.rgb + 0.7f * texColor.rgb, texColor.a);
//    FragColor = texColor;
}
