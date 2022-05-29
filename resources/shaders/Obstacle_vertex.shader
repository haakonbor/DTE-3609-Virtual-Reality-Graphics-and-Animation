// VERTEX SHADER
#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

out vec3 v_TexCoord;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;

void main() {
        gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(position, 1.0);
        v_TexCoord = position;
};
