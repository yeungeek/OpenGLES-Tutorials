package com.yeungeek.opengltutorial.ui.components

import android.annotation.SuppressLint
import android.util.Log
import android.view.SurfaceHolder
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp

/**
 *  Created by jian.yang on 2023/10/15.
 */

@SuppressLint("UnusedMaterial3ScaffoldPaddingParameter")
@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun EGLDetailScreen(title: String, onBackPressed: () -> Unit) {
    Scaffold {
        Box(modifier = Modifier.fillMaxWidth()) {
            ComposableSurfaceView(object : SurfaceHolder.Callback {
                override fun surfaceCreated(holder: SurfaceHolder) {
                    Log.d("EGLActivity", "###### surfaceCreated")
                }

                override fun surfaceChanged(
                    holder: SurfaceHolder,
                    format: Int,
                    width: Int,
                    height: Int
                ) {
                    Log.d("EGLActivity", "###### surfaceChanged")
                }

                override fun surfaceDestroyed(holder: SurfaceHolder) {
                    Log.d("EGLActivity", "###### surfaceDestroyed")
                }
            })

            Box(
                modifier = Modifier
                    .height(50.dp)
                    .fillMaxWidth()
                    .background(
                        color = Color.White,
//                        brush = Brush.verticalGradient(
//                            colors = listOf(
//                                Color.Black.copy(alpha = 0.3f),
//                                Color.Transparent,
//                            ),
//                        )
                    )
            ) {
                Icon(
                    Icons.Filled.ArrowBack,
                    contentDescription = "Icon to navigate back",
                    tint = Color.Black,
                    modifier = Modifier
                        .align(Alignment.TopStart)
                        .clickable {
                            onBackPressed()
                        }
                        .padding(10.dp)
                        .size(28.dp)
                )

                Text(
                    text = title, modifier = Modifier.align(Alignment.Center),
                    style = MaterialTheme.typography.titleSmall,
                    fontWeight = FontWeight.Bold
                )
            }
        }
    }
}

@Preview
@Composable
fun EGLPreview() {
    EGLDetailScreen("EGL Sample") {

    }
}