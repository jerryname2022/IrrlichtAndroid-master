package com.ellismarkov.irrlicht;


import android.content.Context;
import android.util.Log;

public class CrashHandler {
    public static final String TAG = CrashHandler.class.getSimpleName();

    public static Thread.UncaughtExceptionHandler create(Context context) {
        return new Thread.UncaughtExceptionHandler() {
            @Override
            public void uncaughtException(Thread thread, Throwable ex) {
                Log.e(TAG, "崩溃toString>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>: " + ex.toString());
                ex.printStackTrace();
            }
        };
    }
}
