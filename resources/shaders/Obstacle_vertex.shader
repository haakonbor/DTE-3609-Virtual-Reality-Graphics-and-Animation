// VERTEX SHADER
#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;

out vec3 v_TexCoord;
out vec3 v_Normal;
//out vec3 v_LightPositon;
out vec3 v_FragmentPosition;

void main() {
        gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(position, 1.0);

        v_Normal = mat3(transpose(inverse(u_ModelMatrix))) * normal;

        v_FragmentPosition = vec3(u_ModelMatrix * vec4(position, 1.0f));

        v_TexCoord = position;
};
