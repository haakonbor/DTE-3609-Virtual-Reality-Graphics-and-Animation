// FRAGMENT SHADER
#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_LightPosition;
in vec3 v_FragmentPosition;

//uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform sampler2D u_DiffuseMaterial;

void main() {
        vec4 texColor = texture(u_Texture, v_TexCoord);
        //color = texColor;

        // Ambient light
        vec3 ambientLightPos = vec3(0.2f, 0.2f, 0.2f);
        vec3 ambient = ambientLightPos * texture(u_DiffuseMaterial, v_TexCoord).rgb;

        // Diffuse light
        vec3 norm = normalize(v_Normal);
        vec3 lightDir = normalize(v_LightPosition - v_FragmentPosition);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 light_diffuse = vec3(0.5f,0.5f,0.5f);
        vec3 diffuse = light_diffuse * diff * texture(u_DiffuseMaterial, v_TexCoord).rgb;

        // Specular light
        vec3 viewDir = normalize( - v_FragmentPosition);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0f);
        vec3 material_specular = vec3(0.5f,0.5f,0.5f);
        vec3 light_specular = vec3(1.0f,1.0f,1.0f);
        vec3 specular = light_specular * (spec * material_specular);

        vec3 result = ambient + diffuse + specular;

        color = mix(texColor, vec4(result, 1.0f), 0.9);
};
