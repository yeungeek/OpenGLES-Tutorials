package com.yeungeek.opengltutorial.ui.activity

import android.opengl.GLES30
import android.util.Log
import android.view.SurfaceHolder
import android.view.SurfaceHolder.Callback
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import com.yeungeek.opengltutorial.renderer.egl.EGLSample
import com.yeungeek.opengltutorial.ui.components.EGLDetailScreen
import com.yeungeek.opengltutorial.ui.theme.OpenGLTutorialTheme

/**
 *  Created by jian.yang on 2023/10/14.
 */
class EGLActivity : ComponentActivity() {
    private lateinit var mCallback: Callback
    private lateinit var mEGLSample: EGLSample
    override fun onCreate(savedInstanceState: android.os.Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            OpenGLTutorialTheme {
                EGLDetailScreen(mCallback, "EGL Sample") {
                    finish()
                }
            }
        }

        mEGLSample = EGLSample()
        mCallback = object : Callback {
            override fun surfaceCreated(holder: SurfaceHolder) {
                Log.d("EGLActivity", "###### surfaceCreated")
                mEGLSample.initEGL(holder.surface)
                GLES30.glClearColor(1.0f, 0.0f, 0.0f, 1.0f)
            }

            override fun surfaceChanged(
                holder: SurfaceHolder,
                format: Int,
                width: Int,
                height: Int
            ) {
                Log.d("EGLActivity", "###### surfaceChanged")
                GLES30.glViewport(0, 0, width, height)
                GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT)
                mEGLSample.render(width, height)
            }

            override fun surfaceDestroyed(holder: SurfaceHolder) {
                Log.d("EGLActivity", "###### surfaceDestroyed")
//                mEGLSample.release()
            }
        }
    }
}