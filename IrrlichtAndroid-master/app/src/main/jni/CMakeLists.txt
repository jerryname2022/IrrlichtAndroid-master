cmake_minimum_required(VERSION 3.4.1)
set(lib_src_DIR ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI})
INCLUDE_DIRECTORIES(
        ${CMAKE_SOURCE_DIR}
)

add_library(irrlicht_lib STATIC IMPORTED)
set_target_properties(irrlicht_lib PROPERTIES IMPORTED_LOCATION
                             ${lib_src_DIR}/libirrlicht.a)
add_library(game SHARED
            ${CMAKE_SOURCE_DIR}/importgl.cpp
            ${CMAKE_SOURCE_DIR}/app-android.cpp
            ${CMAKE_SOURCE_DIR}/android-activity.cpp
            ${CMAKE_SOURCE_DIR}/android-receiver.cpp
            ${CMAKE_SOURCE_DIR}/CIrrDeviceAndroid.cpp
            ${CMAKE_SOURCE_DIR}/Touch.cpp
            ${CMAKE_SOURCE_DIR}/d3/sceneNode.cpp
)
target_link_libraries(game
log
GLESv1_CM
dl
irrlicht_lib
)

