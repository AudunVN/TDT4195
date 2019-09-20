#version 430 core

in vec3 position;
in layout(location=1) vec4 vertexColor;
uniform layout(location=7) mat4 transform;

out layout(location=1) vec4 outVertexColor;

void main()
{
    outVertexColor = vertexColor;
    gl_Position = vec4(position, 1.0f) * transform;
}
