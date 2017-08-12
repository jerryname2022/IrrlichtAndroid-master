package com.ellismarkov.irrlicht;

import android.app.Application;

/**
 * Application
 */
public class MyApplication extends Application {
  public static final String TAG = MyApplication.class.getSimpleName();//USER_PRESENT


  @Override public void onCreate() {
    super.onCreate();
    Thread.setDefaultUncaughtExceptionHandler(CrashHandler.create(this));
  }
}
