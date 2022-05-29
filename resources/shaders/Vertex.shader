// VERTEX SHADER
#shader vertex 
#version 330 core   
   
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;
//uniform vec4 u_LightPosition;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_LightPositon;
out vec3 v_FragmentPosition;


void main() {   
        gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * position;
        v_Normal = normal;
        v_LightPositon = vec3(u_ViewMatrix * vec4(1.0f, 1.0f, 2.0f, 1.0f));
        v_FragmentPosition = vec3(u_ViewMatrix * u_ModelMatrix * position);
        v_TexCoord = texCoord;
};
