#include "shader.h"
#include "errorChecker.h"
#include <fstream>
GLuint Shader::getShaderProgram(std::string &vertFile, std::string &fragFile, const GLchar *const *FBVayrings){
    checkGlError("Shader");
    shaderID = glCreateProgram();
    GLuint vsShader = loadShader(vertFile.c_str(), GL_VERTEX_SHADER);
    GLuint fgShader = loadShader(fragFile.c_str(), GL_FRAGMENT_SHADER);
    glAttachShader(shaderID, vsShader);
    glAttachShader(shaderID, fgShader);
    if(FBVayrings != NULL) glTransformFeedbackVaryings(shaderID, 4,FBVayrings, GL_SEPARATE_ATTRIBS);
    glLinkProgram(shaderID);
    glUseProgram(shaderID);
    shaderCheck(shaderID);
    glUseProgram(0);
    checkGlError("ShaderEnd");
    return shaderID;
}
GLuint Shader::loadShader(const char* src, GLenum shaderType) {
    GLuint shader =glCreateShader(shaderType);
    glShaderSource(shader,1,&src,NULL);
    if(!shader){
        return 0;
    }
    glShaderSource(shader, 1, &src, NULL);
    GLint compiled = GL_FALSE;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLogLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen > 0) {
            GLchar *infoLog = (GLchar *) malloc(infoLogLen);
            if (infoLog) {
                glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
                ALOGE("Could not compile %s shader:\n%s\n",
                      shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment",
                      infoLog);
                free(infoLog);
            }
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
void Shader::shaderCheck(GLuint program) {
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        ALOGE("Could not link program TF");
        GLint infoLogLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen) {
            GLchar* infoLog = (GLchar*)malloc(infoLogLen);
            if (infoLog) {
                glGetProgramInfoLog(program, infoLogLen, NULL, infoLog);
                ALOGE("Could not link program tf:\n%s\n", infoLog);
                free(infoLog);
            }
        }
        glDeleteProgram(program);
        program = 0;
    }
}