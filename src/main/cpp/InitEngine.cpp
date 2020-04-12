#include <math.h>
#include <vector>
#include <string>
#include <GLES3/gl32.h>
#include<string>
#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "assetManager.h"
#include "draw.h"
#include "errorChecker.h"

static AssetManager* g_assMan = NULL;
static Draw* g_draw = NULL;
static std::vector<std::string> files;

#if !defined(DYNAMIC_ES3)
static GLboolean gl3stubInit() {
    return GL_TRUE;
}
#endif

extern "C"
JNIEXPORT void JNICALL
Java_com_android_gles3jni_GLES3JNILib_init(JNIEnv* env, jclass obj, jintArray jDimension) {
    int *dimension = env->GetIntArrayElements(jDimension, NULL);
    env->ReleaseIntArrayElements(jDimension,dimension,  0);
    const char* versionStr = (const char*)glGetString(GL_VERSION);
    if (strstr(versionStr, "OpenGL ES 3.") ) {
    } else if (strstr(versionStr, "OpenGL ES 2.")) {
        ALOGE("GL VER 2");
    } else {
        ALOGE("Unsupported OpenGL ES version");
    }
    if(files.empty()) {
        ALOGE("No shader files loaded");
    }
    if(g_assMan){
        delete g_draw;
        delete g_assMan;
    }
    g_assMan = new AssetManager();
    g_assMan->initShaderPrograms(files);
    g_assMan->initBuffs();
    g_draw = new Draw(g_assMan);


}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_gles3jni_GLES3JNILib_sendString(JNIEnv *env, jclass obj, jstring stringIn){
    const char *stringOut = env->GetStringUTFChars(stringIn, 0);
    env->ReleaseStringUTFChars(stringIn,stringOut);
    files.push_back(stringOut);
}