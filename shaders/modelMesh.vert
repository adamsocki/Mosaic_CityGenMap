#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normals;

uniform mat4 model;
uniform mat4 viewProjection;
uniform vec4 color;

out vec4 fs_color;
out vec3 fs_normal;
out vec3 frag_pos; 


void main() {

    vec4 worldVert4 = model * vec4(vertexPosition_modelspace, 1.0);
    vec3 worldVert = worldVert4.xyz;
    //worldVert.y += sin(time);
    frag_pos = worldVert;
    
    gl_Position = viewProjection * worldVert4;
    fs_normal = mat3(transpose(inverse(model))) * normals;

    fs_color = color;
}

