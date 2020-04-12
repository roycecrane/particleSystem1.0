#version 300 es
layout(location =  0 ) in vec3 posin;
layout(location = 1 ) in vec3 vel;
layout(location =  2 ) in vec3 outp;
layout(location = 3 ) in vec3 initP;
    out vec3 B;
//    uniform mat4 VPMat;
uniform mat4 VMat;
uniform mat4 PMat;
    void main() {
       B= outp;
        float size = 4.7f;
        gl_PointSize = size;
        gl_Position =vec4(posin.xy,-1.0,1.0f);
    }
//\0
