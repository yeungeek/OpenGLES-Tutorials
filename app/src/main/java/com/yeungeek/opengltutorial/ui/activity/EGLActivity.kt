package com.yeungeek.opengltutorial.ui.activity

import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import com.yeungeek.opengltutorial.ui.components.EGLDetailScreen
import com.yeungeek.opengltutorial.ui.theme.OpenGLTutorialTheme

/**
 *  Created by jian.yang on 2023/10/14.
 */
class EGLActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: android.os.Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            OpenGLTutorialTheme {
                EGLDetailScreen("EGL Sample") {
                    finish()
                }
            }
        }
    }
}