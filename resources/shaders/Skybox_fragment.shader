// FRAGMENT SHADER
#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_TexCoord;

//uniform vec4 u_Color;
uniform samplerCube u_Texture;

void main() {
        vec4 texColor = texture(u_Texture, v_TexCoord);
        color = texColor;
};
