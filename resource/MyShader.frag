#version 330 core

layout(location = 0) out vec4 out_color;

uniform sampler2D sampler_;

in vec3 v_position;
in vec2 v_uv;


void main() {
    out_color = texture(sampler_, v_uv);
}