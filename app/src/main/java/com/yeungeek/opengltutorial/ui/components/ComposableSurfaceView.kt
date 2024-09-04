package com.yeungeek.opengltutorial.ui.components

import android.view.SurfaceHolder
import android.view.SurfaceHolder.Callback
import android.view.SurfaceView
import android.view.ViewGroup
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.viewinterop.AndroidView

@Composable
fun ComposableSurfaceView(callback: Callback, modifier: Modifier = Modifier) {
    AndroidView(factory = { context ->
        SurfaceView(context).apply {
            layoutParams = ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT
            )

            holder.addCallback(callback)
        }
    }, modifier)
}

@Preview
@Composable
fun SurfaceViewPreview() {
    ComposableSurfaceView(object : Callback {
        override fun surfaceCreated(holder: SurfaceHolder) {
            TODO("Not yet implemented")
        }

        override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
            TODO("Not yet implemented")
        }

        override fun surfaceDestroyed(holder: SurfaceHolder) {
            TODO("Not yet implemented")
        }

    })
}