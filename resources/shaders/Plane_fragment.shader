// FRAGMENT SHADER
#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
//in vec3 v_LightPosition;
in vec3 v_FragmentPosition;

//uniform vec4 u_Color;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

void main() {
        vec4 texColor = mix(texture(u_Texture1, v_TexCoord), texture(u_Texture2, v_TexCoord), 0.5);
        //color = texColor;

        vec3 norm = normalize(v_Normal);
        vec3 lightDir = normalize(u_LightPosition - v_FragmentPosition);

        // Ambient light
        vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f);
        vec3 ambient = ambientLight * texColor.rgb;

        // Diffuse light
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 light_diffuse = vec3(0.8f,0.8f,0.8f);
        vec3 diffuse = light_diffuse * diff * texColor.rgb;

        // Specular light
        vec3 viewDir = normalize(u_CameraPosition - v_FragmentPosition);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16.0f);
        vec3 material_specular = vec3(0.5f,0.5f,0.5f);
        vec3 light_specular = vec3(1.0f,1.0f,1.0f);
        vec3 specular = light_specular * (spec * material_specular);

        vec3 result = ambient + diffuse + specular;

        color = mix(texColor, vec4(result, 1.0f), 0.9);
};
