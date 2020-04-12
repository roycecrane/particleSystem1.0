
#ifndef ERRORCHECKER_H
#define ERRORCHECKER_H

#include <android/log.h>

#include <GLES3/gl32.h>
#define DEBUG 1

#define LOG_TAG "GLES3JNI"
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif

bool checkGlError(const char* funcName);
static void printGlString(const char* name, GLenum s);

#endif //ERRORCHECKER_H
