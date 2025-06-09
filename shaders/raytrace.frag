#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform   float ambientStrength;
uniform   float specularStrength;
uniform     int shininess;


uniform vec3 viewPosition;
uniform vec3 lightPosition;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    // === Ambient Component ===
    //const float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // === Diffuse Component ===
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // === Specular Component ===
    //const float specularStrength = 0.5;
    //const int shininess = 32;

    vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    // === Final Lighting ===
    vec3 lighting = (ambient + diffuse + specular) * objectColor;

    // === Texture Blending ===
    vec4 tex1 = texture(texture1, TexCoord);
    vec4 tex2 = texture(texture2, TexCoord);
    vec4 blendedTex = mix(tex1, tex2, 0.5);

    // === Final Color Output ===
    FragColor = vec4(blendedTex.rgb * lighting, blendedTex.a);
}
