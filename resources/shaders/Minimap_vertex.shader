// VERTEX SHADER
#shader vertex 
#version 330 core   
   
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoord;

out vec2 v_TexCoord;

void main() {   
        gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
        v_TexCoord = textureCoord;
};
