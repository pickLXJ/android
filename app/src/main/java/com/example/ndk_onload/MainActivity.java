package com.example.ndk_onload;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toast.makeText(MainActivity.this,jni_onload.test_jni_onload_c(),Toast.LENGTH_SHORT).show();
        Toast.makeText(MainActivity.this,jni_onload.test_jni_onload_cpp(),Toast.LENGTH_SHORT).show();
        Toast.makeText(MainActivity.this,jni_onload.test_jni_onload_c_i_cpp(),Toast.LENGTH_SHORT).show();
        Toast.makeText(MainActivity.this,jni_onload.test_jni_onload_cpp_i_c(),Toast.LENGTH_SHORT).show();

}
}
