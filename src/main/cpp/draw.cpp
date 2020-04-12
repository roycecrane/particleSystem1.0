#include <GLES3/gl32.h>
#include <jni.h>
#include "draw.h"
#include "uniform.h"
#include <time.h>
static AssetManager* d_ass=NULL;
static Draw* g_draw = NULL;
static int drawBuff = 1;
static int frame = 0;
clock_t t1,t2;
static bool reset_now=false;
int of_hundred = 0;
float avg_time = 0.0f;
void Draw::transform() {
    t1=clock();

    glClear(GL_COLOR_BUFFER_BIT);
    d_ass->updateUniform("seeker",NULL);
    d_ass->updateUniform("touch", NULL);
    glUseProgram(d_ass->shaders[0]);
    glEnable(GL_RASTERIZER_DISCARD);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK,d_ass->FBO[drawBuff]);
    glBeginTransformFeedback(GL_POINTS);
    glBindVertexArray(d_ass->VAO[1-drawBuff]);
    glDrawArrays(GL_POINTS, 0, d_ass->numIndices / 3 );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEndTransformFeedback();
    glDisable(GL_RASTERIZER_DISCARD);

}
void Draw::feedBack() {
    glClearColor(0.0f, 0.0f,0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    checkGlError("Adraw");
//    d_ass->updateUniform("PMat",d_ass->PMat);
//    d_ass->updateUniform("VMat",d_ass->VMat);
    glUseProgram(d_ass->shaders[1]);
    glBindVertexArray(d_ass->VAO[drawBuff]);
    glDrawArrays(GL_POINTS ,0 ,d_ass->numIndices/3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    drawBuff = 1 - drawBuff;
    checkGlError("draw");
    t2=clock();
    float diff ((float)t2-(float)t1);
    frame ++;
    of_hundred ++;
    avg_time += diff/CLOCKS_PER_SEC;
    if(of_hundred == 100){
        __android_log_print(ANDROID_LOG_ERROR, "time", "%f",avg_time);
        avg_time = 0.0f;
        of_hundred = 0;
    }
    if(reset_now){
        d_ass->resetBuffers();
        reset_now = false;
    }
}
Draw::Draw(AssetManager* ass) {
    d_ass = ass;
    g_draw = this;
    }

extern "C" {
JNIEXPORT void JNICALL Java_com_android_gles3jni_GLES3JNILib_reset(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL Java_com_android_gles3jni_GLES3JNILib_step(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL Java_com_android_gles3jni_GLES3JNILib_inputs(JNIEnv * env , jclass obj, jfloatArray userInput , jstring inputName ) ;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_android_gles3jni_GLES3JNILib_step(JNIEnv* env, jclass obj) {
    g_draw->transform();
    g_draw->feedBack();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_android_gles3jni_GLES3JNILib_inputs(JNIEnv* env, jclass obj,jfloatArray userInput,jstring inputName) {
    float *InputToCPP = env->GetFloatArrayElements(userInput,0 );
    env->ReleaseFloatArrayElements(userInput,InputToCPP, 0);
    const char *name = env->GetStringUTFChars(inputName, 0);
    env->ReleaseStringUTFChars(inputName,name);
d_ass->updateUniform(name,InputToCPP);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_android_gles3jni_GLES3JNILib_reset(JNIEnv* env, jclass obj) {
    ALOGE("reset");
    reset_now = true;
}
//    unsigned size = (float)env->GetArrayLength(userInput);