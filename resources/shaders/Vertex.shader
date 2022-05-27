// VERTEX SHADER
#shader vertex 
#version 330 core   
   
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;

void main() {   
        gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * position;
        v_TexCoord = texCoord;
};
