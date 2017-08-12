# COSOperator.cpp was removed from IRROTHEROBJ
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
ANDROID = importgl.cpp app-android.cpp android-activity.cpp android-receiver.cpp CIrrDeviceAndroid.cpp Touch.cpp ./d3/sceneNode.cpp
LOCAL_MODULE := game
LOCAL_SRC_FILES := $(ANDROID)
LOCAL_LDFLAGS := $(LOCAL_PATH)/libs/$(TARGET_ARCH_ABI)/libirrlicht.a
LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog
include $(BUILD_SHARED_LIBRARY)
