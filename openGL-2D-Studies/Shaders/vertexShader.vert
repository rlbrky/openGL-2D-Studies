#version 330

layout(location = 0) in vec3 inPosition;

uniform mat3 uMtxTransform;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main(){
    //gl_Position = uProjection * uView * uModel * vec4(uMtxTransform * inPosition, 1.0f);
    //gl_Position = uProjection * vec4(inPosition, 1.0f);
    gl_Position = vec4(uMtxTransform * inPosition, 1.0f);
}