package com.example.hellojni;

public class CmPractice {
    static {
        System.loadLibrary("hello-jni");
    }

    public native long now_ms();

    public native String ctime();

    public native String getHostFromUrl(String url);
}
