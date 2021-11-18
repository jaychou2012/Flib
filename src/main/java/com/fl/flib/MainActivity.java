package com.fl.flib;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.TextView;

import com.fl.flib.databinding.ActivityMainBinding;

import org.fmod.FMOD;

import java.io.File;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        FMOD.init(this);

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText("fdslfjdal");
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        Utils.saveSoundAsync(Environment.getExternalStorageDirectory().getPath() + "/1.wav", Utils.MODE_UNCLE,
                                Environment.getExternalStorageDirectory().getPath() + "/3.wav", new Utils.ISaveSoundListener() {
                                    @Override
                                    public void onFinish(String path, String savePath, int type) {

                                    }

                                    @Override
                                    public void onError(String msg) {

                                    }
                                });
                    }
                }).start();

//                Utils.saveSoundAsync(Environment.getExternalStorageDirectory().getPath() + "/1.wav", Utils.MODE_UNCLE,
//                        Environment.getExternalStorageDirectory().getPath() + "/3.wav", new Utils.ISaveSoundListener() {
//                            @Override
//                            public void onFinish(String path, String savePath, int type) {
//
//                            }
//
//                            @Override
//                            public void onError(String msg) {
//
//                            }
//                        });
            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }

}