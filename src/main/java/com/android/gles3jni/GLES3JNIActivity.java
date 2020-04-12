package com.android.gles3jni;
import com.android.gles3jni.BuildConfig;
import android.app.Activity;
import android.content.Context;
import android.hardware.SensorEventListener;
import android.os.Bundle;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.Spinner;

import java.util.jar.Attributes;


public class GLES3JNIActivity extends Activity {
    SeekBar seekBar;

    private long startTime;
    GLES3JNIView mView;
    private Button mButton;
    float [] buttonPressed ={1.0f,0.0f,0.0f};
    @Override protected void onCreate(Bundle icicle) {
        MyStuff myobj;
        new MyStuff(GLES3JNIActivity.this);
        super.onCreate(icicle);
        startTime = System.currentTimeMillis();
        setContentView(R.layout.layout);

        mView = (GLES3JNIView) findViewById(R.id.GLES3JNIView2);
        AttributeSet attribs = null;

        mView = new GLES3JNIView(getApplication(), attribs);
         seekBar=(SeekBar)findViewById(R.id.seekBar);
        int progress = seekBar.getProgress();


        mButton = findViewById(R.id.button);
        mButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
               buttonPressed[0] *= -1.0f;
               GLES3JNILib.reset();
            }
        });
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int pval = 0;
            String inputName = "seeker";

            float[] seekerInput = {1.0f,0.0f,0.0f};

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                seekerInput[0] = (float)progress;
                GLES3JNILib.inputs(seekerInput,"seeker");
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                //write custom code to on start progress
            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

                GLES3JNILib.inputs(seekerInput,inputName);
            }
        });
   }

    @Override protected void onPause() {
        super.onPause();
//        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
//        mView.onResume();
    }
    public long getRunningTimeMillis() {
        return System.currentTimeMillis() - startTime;

    }



}



