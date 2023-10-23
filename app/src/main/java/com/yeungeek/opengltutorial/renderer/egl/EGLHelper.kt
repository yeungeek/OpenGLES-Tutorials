package com.yeungeek.opengltutorial.renderer.egl

import android.opengl.EGL14
import android.opengl.EGLConfig
import android.opengl.EGLContext
import android.opengl.EGLDisplay
import android.opengl.EGLSurface
import android.util.Log
import android.view.Surface

/**
 *  Created by jian.yang on 2023/10/15.
 */
class EGLHelper {

    private var mEGLDisplay: EGLDisplay = EGL14.EGL_NO_DISPLAY
    private var mEGLContext: EGLContext = EGL14.EGL_NO_CONTEXT

    private var mEGLConfig: EGLConfig? = null
    private lateinit var mEGLSurface: EGLSurface

    private val EGL_SURFACE = intArrayOf(
        EGL14.EGL_NONE
    )

    var mMajorVersion = IntArray(1)
    var mMinorVersion = IntArray(1)

    private val EGL_ATTRIBUTE = intArrayOf(
        EGL14.EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL14.EGL_NONE
    )

    private val EGL_CONFIG = intArrayOf(
        EGL14.EGL_RED_SIZE, 8,
        EGL14.EGL_GREEN_SIZE, 8,
        EGL14.EGL_BLUE_SIZE, 8,
        EGL14.EGL_ALPHA_SIZE, 8,
        EGL14.EGL_DEPTH_SIZE, 16,
        EGL14.EGL_STENCIL_SIZE, 0,
        EGL14.EGL_RENDERABLE_TYPE, EGL14.EGL_OPENGL_ES2_BIT,
        EGL14.EGL_NONE
    )

    fun initEGL(surface: Surface) {
        //1. get display
        mEGLDisplay = EGL14.eglGetDisplay(EGL14.EGL_DEFAULT_DISPLAY)
        if (mEGLDisplay == EGL14.EGL_NO_DISPLAY) {
            //
            Log.e("EGLSample", "###### EGL get display failed");
            return
        }

        //2.init
        val result = EGL14.eglInitialize(mEGLDisplay, mMajorVersion, 0, mMinorVersion, 0)
        if (!result) {
            Log.e("EGLSample", "###### EGL initialize failed")
            return
        }

        //3. choose egl config
        val configs = arrayOfNulls<EGLConfig>(1)
        val numConfigs = IntArray(1)
        EGL14.eglChooseConfig(mEGLDisplay, EGL_CONFIG, 0, null, 0, 0, numConfigs, 0)

        val num = numConfigs[0]
        if (num != 0) {
            EGL14.eglChooseConfig(
                mEGLDisplay,
                EGL_CONFIG,
                0,
                configs,
                0,
                configs.size,
                numConfigs,
                0
            )

            mEGLConfig = configs[0]
            Log.d("EGLSample", "###### eglconfig")
        }

        //4. create context
        mEGLContext =
            EGL14.eglCreateContext(mEGLDisplay, mEGLConfig, EGL14.EGL_NO_CONTEXT, EGL_ATTRIBUTE, 0)
        if (mEGLContext == EGL14.EGL_NO_CONTEXT) {
            Log.e("EGLSample", "###### EGL create context failed");
            return
        }

        //5. create surface
        mEGLSurface = EGL14.eglCreateWindowSurface(mEGLDisplay, mEGLConfig, surface, EGL_SURFACE, 0)

        //6. current
        EGL14.eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext)
//
//        //init
//        EGLTexture.initTexture()
    }

    fun render(width: Int, height: Int) {
        //7. draw
//        EGLTexture.draw(width, height)
        //8. swap buffer
        EGL14.eglSwapBuffers(mEGLDisplay, mEGLSurface)
    }

    fun release() {
        EGL14.eglMakeCurrent(
            mEGLDisplay,
            EGL14.EGL_NO_SURFACE,
            EGL14.EGL_NO_SURFACE,
            EGL14.EGL_NO_CONTEXT
        )

        EGL14.eglDestroyContext(mEGLDisplay, mEGLContext)
        EGL14.eglDestroySurface(mEGLDisplay, mEGLSurface)
        EGL14.eglReleaseThread()
        EGL14.eglTerminate(mEGLDisplay)

        mEGLContext = EGL14.EGL_NO_CONTEXT
        mEGLSurface = EGL14.EGL_NO_SURFACE
        mEGLConfig = null
    }
}