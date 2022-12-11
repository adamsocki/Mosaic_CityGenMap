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
	vec3 positionChange = pOffset;
    vec4 worldVert4 = model * vec4(vertexPosition_modelspace + positionChange, 1.0f);
	worldVert4.x = worldVert4.x + pOffset.x;
    vec3 worldVert = worldVert4.xyz;
	
	
	//positionChange.x += vertexPosition_modelspace.x;
	//positionChange.y += vertexPosition_modelspace.y;
	//positionChange.z += vertexPosition_modelspace.z;
    
    gl_Position = viewProjection * worldVert4 * vec4(positionChange, 1.0f);

    fs_color = color;

    texcoord = in_texcoord;

    fs_normal = normals;
}

