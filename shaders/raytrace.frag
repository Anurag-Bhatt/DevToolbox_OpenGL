#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    // Blend the two textures
    vec4 texColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);

    // Apply lighting factor (objectColor * lightColor)
    vec3 lighting = lightColor * objectColor;

    // Multiply lighting with the texture color (only RGB, preserve alpha)
    FragColor = vec4(texColor.rgb * lighting, texColor.a);
}