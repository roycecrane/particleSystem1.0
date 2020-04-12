package com.android.gles3jni;

import java.io.IOException;
import java.io.InputStream;

public class MyStuff {
    static String s1 = "1shader.vs";
    static String s2 = "2shader.vs";
    static String s3 = "1shader.fs";
    static String s4 = "2shader.fs";

    static String inFile= "";
    public  MyStuff(GLES3JNIActivity act){

        try {

            InputStream stream = act.getAssets().open(s1);
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            s1 = new String(buffer);

        } catch (IOException e) {
            // Handle exceptions here
        }
        try {

            InputStream stream = act.getAssets().open(s2);
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            s2 = new String(buffer);
        } catch (IOException e) {
            // Handle exceptions here
        }
        try {

            InputStream stream = act.getAssets().open(s3);
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            s3 = new String(buffer);
        } catch (IOException e) {
            // Handle exceptions here
        }

        try {

            InputStream stream = act.getAssets().open(s4);
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            s4 = new String(buffer);
        } catch (IOException e) {
            // Handle exceptions here
        }
    }
    public static String getData1(){
        return s1;
    }
    public static String getData2(){
        return s2;
    }
    public static String getData3(){
        return s3;
    }
    public static String getData4(){
        return s4;
    }
}
