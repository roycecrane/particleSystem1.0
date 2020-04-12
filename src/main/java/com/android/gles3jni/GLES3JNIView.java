

package com.android.gles3jni;

import android.app.Activity;
import android.content.Context;
import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;
import android.os.Environment;

import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;

import android.opengl.Matrix;
import android.view.MotionEvent;


import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

class GLES3JNIView extends GLSurfaceView {
    private static final String TAG = "GLES3JNI";
    private static final boolean DEBUG = true;
    public boolean first =true;
    static float[] inputArray = {0.0f,0.0f,0.0f};
    float[] mVmat;
    static int m_width;
    static int m_height;
    float gravity=1.0f;
    static float x=0.0f;

    static float y=0.0f;
    static float width  = (float)m_width;
    static float height =(float)m_height;

    public GLES3JNIView(Context context, AttributeSet attribs) {
        super(context);

        setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        setEGLContextClientVersion(3);
        setRenderer(new Renderer());

    }

    private static class Renderer implements GLSurfaceView.Renderer {

        private final float[] pMat = new float[16];
        private final float[] vPMatrix = new float[16];
        private final float[] vMat = new float[16];


        public void onDrawFrame(GL10 gl) {
            float ratio = (float) m_width / (float)m_height;
            GLES30.glViewport(0, 0, m_width, m_height);
            Matrix.frustumM(pMat, 0, -ratio, ratio, -1, 1, 1, 300);
            Matrix.setLookAtM(vMat, 0, 0.1f, 0.1f, -2.0f, 0.1f, 0.1f, 0f, 1f, -0f, 5f);
//            Matrix.multiplyMM(vPMatrix, 1, pMat, 1, vMat, 1);
            GLES3JNILib.inputs(pMat,"PMat");
            GLES3JNILib.inputs(vMat,"VMat");
            GLES3JNILib.step();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            String VSA = MyStuff.getData1();
            String VSB = MyStuff.getData2();
            String FSA = MyStuff.getData3();
            String FSB = MyStuff.getData4();

            m_width  = width;
            m_height = height;

            float ratio = (float) width / (float)height;
            GLES30.glViewport(0, 0, width, height);
            Matrix.frustumM(pMat, 0, -ratio, ratio, -1, 1, 1, 300);

            GLES3JNILib.sendString(VSB);
            GLES3JNILib.sendString(FSB);
            GLES3JNILib.sendString(VSA);
            GLES3JNILib.sendString(FSA);

            int [] displayDimension = new int[]{width, height};
            GLES3JNILib.init(displayDimension);
            GLES3JNILib.inputs(vMat,"VMat");

        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        }

    }
    public void setViewProjection() {

    }
    @Override
    public boolean onTouchEvent(MotionEvent e) {


        switch (e.getAction()) {
            case MotionEvent.ACTION_DOWN:
                 y = e.getY();
                 x = e.getX();
                inputArray[0] = -0.5f+(x-width/2.0f)/(float)m_width;
                inputArray[1] = 0.5f-(y- height/2.0f)/(float)m_height;
                inputArray[0]*= 2.0f;
                inputArray[1]*= 2.0f;

               break;
            case MotionEvent.ACTION_UP:

                break;
            case (MotionEvent.ACTION_CANCEL) :

            break;

            default:

                break;

        }





        GLES3JNILib.inputs(inputArray,"touch");

        return true;

    }

}