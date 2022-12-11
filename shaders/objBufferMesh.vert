#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 in_texcoord;
layout(location = 3) in vec3 pOffset;

uniform mat4 model;
uniform mat4 viewProjection;
uniform vec4 color;

out vec2 texcoord;

out vec4 fs_color;
out vec3 fs_normal;

void main() {
    vec4 worldVert4 = model * vec4(vertexPosition_modelspace, 1.0f);
    vec3 worldVert = worldVert4.xyz;
    
    gl_Position = viewProjection * worldVert4 * vec4(pOffset, 1.0f);

    fs_color = color;

    texcoord = in_texcoord;

    fs_normal = normals;
}

