#ifndef BUFFERINIT_H
#define BUFFERINIT_H
#include <iostream>
#include <vector>
#include <GLES3/gl32.h>
class Buffer{
public:
    static GLuint totalBufferNumber;
     GLuint m_bufferID[2]; // genBuff ID
     int m_indexCount;
     float* m_data;
     GLuint m_attributeIndex = 0;
    void fillBuffer();
     Buffer(float* data, int size, GLuint * VAO, GLuint * FBO);
    ~Buffer();
};
#endif //BUFFERINIT_H
