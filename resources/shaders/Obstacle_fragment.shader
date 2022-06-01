// FRAGMENT SHADER
#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_TexCoord;
in vec3 v_Normal;
//in vec3 v_LightPosition;
in vec3 v_FragmentPosition;

//uniform vec4 u_Color;
uniform samplerCube u_Texture;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

void main() {
        vec4 texColor = texture(u_Texture, v_TexCoord);
//        color = texColor;

        vec3 norm = normalize(v_Normal);
        vec3 lightDir = normalize(u_LightPosition - v_FragmentPosition);

        // Ambient light
        vec4 ambientLight = vec4(0.1f, 0.1f, 0.1f, 1.0f);
        vec4 ambient = ambientLight * texColor;

        // Diffuse light
        float diff = max(dot(norm, lightDir), 0.0);
        vec4 light_diffuse = vec4(0.8f,0.8f,0.8f, 1.0f);
        vec4 diffuse = light_diffuse * diff * texColor;

        // Specular light
        vec3 viewDir = normalize(u_CameraPosition - v_FragmentPosition);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
        vec4 material_specular = vec4(0.2f,0.2f,0.2f, 1.0f);
        vec4 light_specular = vec4(1.0f,1.0f,1.0f, 1.0f);
        vec4 specular = light_specular * (spec * material_specular);

        vec4 result = ambient + diffuse + specular;

        color = mix(texColor, result, 0.9);
};
