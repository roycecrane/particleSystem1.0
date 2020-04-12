#ifndef SHADER_H
#define SHADER_H 1
#include <vector>
#include <iostream>
#include <GLES3/gl32.h>

class Shader{
public:
    GLuint shaderID;
    GLint linked;
    GLuint loadShader(const char* src, GLenum shaderType);
    void shaderCheck(GLuint program);
    GLuint getShaderProgram(std::string &vertFile, std::string &fragFile, const GLchar *const *FBVayrings);
    };

#endif //SHADER_H
