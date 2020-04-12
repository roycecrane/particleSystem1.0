#include "assetManager.h"
#include "errorChecker.h"
#include "shader.h"
#define SHAPE_X 2000
#define SHAPE_Y 2000
static std::vector<Uniform>  uniforms;
void AssetManager::updateUniform(std::string uniName,float *data) {

    auto uniPtr = std::find_if(std::begin(uniforms), std::end(uniforms),
                               [&](Uniform const& uID)
                               { return uID.m_name == uniName.c_str(); });
    uniPtr->setUniform("ALREADY_SET",data);
}
void AssetManager::initShaderPrograms(std::vector<std::string> &shaderFiles) {
    const GLchar* FBVayrings[4] = {"P", "V", "O","IP"};
    Shader* shader = new Shader;
    shaders.push_back(shader->getShaderProgram(shaderFiles[2], shaderFiles[1], FBVayrings));
    shaders.push_back(shader->getShaderProgram(shaderFiles[0], shaderFiles[3], NULL));

    //DEFINE UNIFORMS
    uniforms.push_back(Uniform(shaders[0], "touch", "VEC3"));
    uniforms.push_back(Uniform(shaders[0], "seeker", "VEC3"));
    uniforms.push_back(Uniform(shaders[0], "button", "VEC3"));
    uniforms.push_back(Uniform(shaders[1], "VMat", "MAT4"));
    uniforms.push_back(Uniform(shaders[1], "PMat", "MAT4"));
    delete shader;
}
void AssetManager::resetBuffers(){
    for (int i = 0; i < buffers.size() ; ++i) {
        buffers[i].fillBuffer();
    }
}
void AssetManager::initBuffs(){
    numIndices = SHAPE_X * SHAPE_Y;
    float* pos = new float[numIndices];
    float* vel = new float[numIndices];
    particleSystem* p = new particleSystem(pos, vel, SHAPE_X, SHAPE_Y);
    World* world;
    world = p;
    world->initMeshData();

    FBO = new GLuint[2];
    VAO = new GLuint[2];

    buffers.push_back(Buffer( pos, numIndices, VAO, FBO));
    buffers.push_back(Buffer( vel, numIndices, VAO, FBO));
    buffers.push_back(Buffer( NULL, numIndices, VAO, FBO));
    buffers.push_back(Buffer( pos, numIndices, VAO, FBO));
    checkGlError("0");
}
AssetManager::~AssetManager() {
}
