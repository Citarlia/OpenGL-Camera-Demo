#version 330 core

layout(location = 0)in vec3 in_position;
layout(location = 1)in vec2 in_uv;

out vec3 v_position;
out vec2 v_uv;

uniform float u_time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
    mat3 rotate_m = mat3(
        cos(u_time), -sin(u_time), 0.0,
        sin(u_time),  cos(u_time), 0.0,
        0.0,          0.0        , 1.0);
    vec4 position = vec4(in_position, 1);
    position = projection * view * model * position;
    gl_Position = position;
    v_position = in_position;
    v_uv = in_uv;
}