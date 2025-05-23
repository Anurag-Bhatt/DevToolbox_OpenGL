#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 newColor;

uniform float xTransform;
uniform float yTransform;

void main()
{
    gl_Position = vec4(aPos.x * xTransform, -aPos.y * yTransform, aPos.z, 1.0);
    newColor = aCol;
}