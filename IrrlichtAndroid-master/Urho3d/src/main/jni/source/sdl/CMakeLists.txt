#
# Copyright (c) 2008-2016 the Urho3D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

set(SDL_src_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SDL_src_list ${SDL_src_DIR}/SDL_hints.c
                   ${SDL_src_DIR}/SDL.c
                   ${SDL_src_DIR}/SDL_error.c
                   ${SDL_src_DIR}/SDL_assert.c
                   ${SDL_src_DIR}/SDL_log.c
                   ${SDL_src_DIR}/atomic/SDL_spinlock.c
                   ${SDL_src_DIR}/atomic/SDL_atomic.c
                   ${SDL_src_DIR}/libm/e_rem_pio2.c
                   ${SDL_src_DIR}/libm/s_sin.c
                   ${SDL_src_DIR}/libm/k_rem_pio2.c
                   ${SDL_src_DIR}/libm/k_sin.c
                   ${SDL_src_DIR}/libm/s_fabs.c
                   ${SDL_src_DIR}/libm/s_cos.c
                   ${SDL_src_DIR}/libm/k_cos.c
                   ${SDL_src_DIR}/libm/k_tan.c
                   ${SDL_src_DIR}/libm/e_sqrt.c
                   ${SDL_src_DIR}/libm/s_atan.c
                   ${SDL_src_DIR}/libm/e_atan2.c
                   ${SDL_src_DIR}/libm/s_floor.c
                   ${SDL_src_DIR}/libm/s_copysign.c
                   ${SDL_src_DIR}/libm/s_scalbn.c
                   ${SDL_src_DIR}/libm/s_tan.c
                   ${SDL_src_DIR}/libm/e_pow.c
                   ${SDL_src_DIR}/libm/e_log.c
                   ${SDL_src_DIR}/stdlib/SDL_iconv.c
                   ${SDL_src_DIR}/stdlib/SDL_string.c
                   ${SDL_src_DIR}/stdlib/SDL_stdlib.c
                   ${SDL_src_DIR}/stdlib/SDL_malloc.c
                   ${SDL_src_DIR}/stdlib/SDL_getenv.c
                   ${SDL_src_DIR}/stdlib/SDL_qsort.c
                   ${SDL_src_DIR}/thread/SDL_thread.c
                   ${SDL_src_DIR}/timer/SDL_timer.c
                   ${SDL_src_DIR}/audio/SDL_audiotypecvt.c
                   ${SDL_src_DIR}/audio/SDL_audiodev.c
                   ${SDL_src_DIR}/audio/SDL_mixer.c
                   ${SDL_src_DIR}/audio/SDL_audio.c
                   ${SDL_src_DIR}/audio/SDL_wave.c
                   ${SDL_src_DIR}/audio/SDL_audiocvt.c
                   ${SDL_src_DIR}/cpuinfo/SDL_cpuinfo.c
                   ${SDL_src_DIR}/events/SDL_keyboard.c
                  ${SDL_src_DIR}/events/SDL_windowevents.c
                  ${SDL_src_DIR}/events/SDL_touch.c
                  ${SDL_src_DIR}/events/SDL_dropevents.c
                  ${SDL_src_DIR}/events/SDL_events.c
                  ${SDL_src_DIR}/events/SDL_gesture.c
                  ${SDL_src_DIR}/events/SDL_clipboardevents.c
                  ${SDL_src_DIR}/events/SDL_mouse.c
                  ${SDL_src_DIR}/events/SDL_quit.c
                  ${SDL_src_DIR}/file/SDL_rwops.c
                  ${SDL_src_DIR}/haptic/SDL_haptic.c
                  ${SDL_src_DIR}/joystick/SDL_gamecontroller.c
                  ${SDL_src_DIR}/joystick/SDL_joystick.c
                  ${SDL_src_DIR}/power/SDL_power.c
                  ${SDL_src_DIR}/video/SDL_bmp.c
                  ${SDL_src_DIR}/video/SDL_blit_slow.c
                  ${SDL_src_DIR}/video/SDL_egl.c
                  ${SDL_src_DIR}/video/SDL_stretch.c
                  ${SDL_src_DIR}/video/SDL_blit.c
                  ${SDL_src_DIR}/video/SDL_blit_A.c
                  ${SDL_src_DIR}/video/SDL_surface.c
                  ${SDL_src_DIR}/video/SDL_blit_auto.c
                  ${SDL_src_DIR}/video/SDL_blit_copy.c
                  ${SDL_src_DIR}/video/SDL_RLEaccel.c
                  ${SDL_src_DIR}/video/SDL_pixels.c
                  ${SDL_src_DIR}/video/SDL_blit_0.c
                  ${SDL_src_DIR}/video/SDL_rect.c
                  ${SDL_src_DIR}/video/SDL_clipboard.c
                  ${SDL_src_DIR}/video/SDL_blit_1.c
                  ${SDL_src_DIR}/video/SDL_fillrect.c
                  ${SDL_src_DIR}/video/SDL_shape.c
                  ${SDL_src_DIR}/video/SDL_video.c
                  ${SDL_src_DIR}/video/SDL_blit_N.c
                  ${SDL_src_DIR}/audio/dummy/SDL_dummyaudio.c
                  ${SDL_src_DIR}/audio/disk/SDL_diskaudio.c
                  ${SDL_src_DIR}/video/dummy/SDL_nullvideo.c
                  ${SDL_src_DIR}/video/dummy/SDL_nullframebuffer.c
                  ${SDL_src_DIR}/video/dummy/SDL_nullevents.c
                  ${SDL_src_DIR}/loadso/dlopen/SDL_sysloadso.c
                  ${SDL_src_DIR}/timer/unix/SDL_systimer.c
                  ${SDL_src_DIR}/thread/pthread/SDL_systhread.c
                  ${SDL_src_DIR}/thread/pthread/SDL_sysmutex.c
                  ${SDL_src_DIR}/thread/pthread/SDL_syscond.c
                  ${SDL_src_DIR}/thread/pthread/SDL_systls.c
                  ${SDL_src_DIR}/thread/pthread/SDL_syssem.c
                  ${SDL_src_DIR}/core/android/SDL_android.c
                  ${SDL_src_DIR}/audio/android/SDL_androidaudio.c
                  ${SDL_src_DIR}/filesystem/android/SDL_sysfilesystem.c
                  ${SDL_src_DIR}/joystick/android/SDL_sysjoystick.c
                  ${SDL_src_DIR}/power/android/SDL_syspower.c
                  ${SDL_src_DIR}/video/android/SDL_androidmouse.c
                  ${SDL_src_DIR}/video/android/SDL_androidmessagebox.c
                  ${SDL_src_DIR}/video/android/SDL_androidwindow.c
                  ${SDL_src_DIR}/video/android/SDL_androidgl.c
                  ${SDL_src_DIR}/video/android/SDL_androidtouch.c
                  ${SDL_src_DIR}/video/android/SDL_androidclipboard.c
                  ${SDL_src_DIR}/video/android/SDL_androidkeyboard.c
                  ${SDL_src_DIR}/video/android/SDL_androidvideo.c
                  ${SDL_src_DIR}/video/android/SDL_androidevents.c
                  ${SDL_src_DIR}/haptic/dummy/SDL_syshaptic.c
)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../.././include/Urho3D)

add_library(SDL STATIC
            ${SDL_src_list}
)
target_link_libraries(SDL
dl
log
android
GLESv1_CM
GLESv2
m )

