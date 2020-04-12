#include "uniform.h"
#include "errorChecker.h"
int Uniform::numUniforms = 0;
Uniform::Uniform(GLuint progID, std::string name,const char*type) {
    m_name = name;
    m_type = type;
    m_progID = progID;
    m_ID = numUniforms;
    numUniforms += 1;
    m_uniformID = (glGetUniformLocation(progID, m_name.c_str()));

    if(strcmp(type ,"MAT4")==0){
        m_data = new float[16]{0};
        m_length = 16;
    };
    if(strcmp(type ,"VEC3")==0)
    {
        m_data = new float[3]{0};
        m_length = 3;
    };

}
void Uniform::setUniform(const char* type, float* data){
    if(data != NULL ){
        for (int i = 0; i <m_length ; ++i) {
            m_data[i] = data[i];
        }
    }else {

        if (strcmp(type, "ALREADY_SET") == 0) type = m_type;
        glUseProgram(m_progID);
        if (strcmp(type, "MAT4") == 0) glUniformMatrix4fv(m_uniformID, 1, GL_FALSE, m_data);
        if (strcmp(type, "VEC3") == 0) glUniform3f(m_uniformID, m_data[0], m_data[1], m_data[3]);
        glUseProgram(0);
    }
    if(m_name=="button"){
        __android_log_print(ANDROID_LOG_ERROR, "slider", "%f",m_data[0]);

    }
}









