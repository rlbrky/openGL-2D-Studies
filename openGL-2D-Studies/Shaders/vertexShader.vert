#version 330

layout(location = 0) in vec3 inPosition;

uniform mat3 uMtxTransform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(){
    gl_Position = proj * view * model * vec4(uMtxTransform * inPosition, 1.0f);
}