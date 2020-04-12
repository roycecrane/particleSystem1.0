#version 300 es
precision mediump float;
out vec4 outColor;
in vec3 B;
void main() {
outColor = vec4(1.0f,1.0,0.0f,0.5f);

outColor = vec4(B,0.5f);
}
//\0