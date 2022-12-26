#version 330

layout(location = 0) in vec3 inPosition;

uniform vec3 uSet;

void main(){
    gl_Position = vec4(inPosition+uSet, 1.0);
}