#version 330 core

in vec2 texcoord;

in vec4 fs_color;
out vec4 fragColor;
in vec3 fs_normal;

uniform sampler2D texture0;
//out vec4 color_;

void main(void){

    fragColor = fs_color;
     vec2 uv = texcoord;

    vec4 textureContrib = texture(texture0, uv).rgba;
    
    fragColor.rgba = textureContrib;

}

