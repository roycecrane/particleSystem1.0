#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <iostream>
#include <GLES3/gl32.h>
#include "World.h"
#include "uniform.h"
#include "BufferInit.h"

class AssetManager{
public:
    AssetManager(){};
    std::vector<Buffer> buffers;
    void resetBuffers();
    void initBuffs();
    void initShaderPrograms(std::vector<std::string> &shaderFiles);
    void updateUniform(std::string uniName,float *data);

    std::vector<GLuint> shaders;
    std::vector<Uniform>  uniforms;

     GLuint* VAO;
     GLuint* FBO;
     int numIndices;
    ~AssetManager();
};




#endif //ASSETMANAGER_H

