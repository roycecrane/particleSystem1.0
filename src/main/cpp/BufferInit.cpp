#include "BufferInit.h"
#include "errorChecker.h"
GLuint Buffer::totalBufferNumber = 0;
Buffer::Buffer(float* data, int size,GLuint * VAO, GLuint * FBO)
{
    checkGlError("Buffer");
    if( totalBufferNumber == 0) {
        glGenVertexArrays(2,VAO);
        glGenTransformFeedbacks(2, FBO);
    }
    m_attributeIndex = totalBufferNumber;
    totalBufferNumber++;
    m_data = data;
    m_indexCount = size;
    glGenBuffers(2,m_bufferID);
    fillBuffer();

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[0]);
    glVertexAttribPointer(m_attributeIndex, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), 0);
    glEnableVertexAttribArray(m_attributeIndex);
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[1]);
    glVertexAttribPointer(m_attributeIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(m_attributeIndex);
    glBindVertexArray(0);

    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FBO[0]);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, m_attributeIndex, m_bufferID[0]);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FBO[1]);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, m_attributeIndex, m_bufferID[1]);
    checkGlError("BufferEND");
}
void Buffer::fillBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[0]);
    glBufferData(GL_ARRAY_BUFFER, m_indexCount * sizeof(GLfloat), NULL, GL_DYNAMIC_COPY);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[1]);
    glBufferData(GL_ARRAY_BUFFER, m_indexCount * sizeof(GLfloat), NULL, GL_DYNAMIC_COPY);

    if(m_data != NULL) {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_indexCount * sizeof(GLfloat), &m_data[0]);
    }
    checkGlError("fillBuffer");

}
Buffer::~Buffer() {
}







