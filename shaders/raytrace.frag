#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 viewPosition;
uniform vec3 lightPosition;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    // Ambient
    float ambientStrength = 0.1; // strength of ambient light
    
    // Diffusion
    vec3 normalizedNormal   = normalize(Normal);
    vec3 normalizedLightDirection = normalize(lightPosition - FragPos);
    float diffuseImpact = max(dot(normalizedNormal, normalizedLightDirection), 0.0);

    // Specular
    vec3 viewDirection = normalize(viewPosition - FragPos);
    vec3 reflectDirection = reflect(-normalizedLightDirection, normalizedNormal);
    float specularStrength = 0.5;
    int shininess = 32;
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
    float specular = specularStrength * spec;

    // Apply lighting factor
    vec3 lightingResult = (lightColor * (ambientStrength + diffuseImpact + specular)) * objectColor;

    // Blend the two textures
    vec4 texColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
    // Multiply lighting with the texture color (only RGB, preserve alpha)
    FragColor = vec4(texColor.rgb * lightingResult, texColor.a);

}