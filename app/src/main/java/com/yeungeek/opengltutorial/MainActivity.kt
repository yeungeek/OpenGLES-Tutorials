package com.yeungeek.opengltutorial

import android.annotation.SuppressLint
import android.content.Intent
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Surface
import androidx.compose.material3.windowsizeclass.ExperimentalMaterial3WindowSizeClassApi
import androidx.compose.material3.windowsizeclass.calculateWindowSizeClass
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.lifecycle.lifecycleScope
import com.google.accompanist.adaptive.calculateDisplayFeatures
import com.yeungeek.opengltutorial.data.Sample
import com.yeungeek.opengltutorial.data.local.LocalSampleDataProvider
import com.yeungeek.opengltutorial.ui.activity.EGLActivity
import com.yeungeek.opengltutorial.ui.activity.ShaderDetailActivity
import com.yeungeek.opengltutorial.ui.components.SampleListContent
import com.yeungeek.opengltutorial.ui.theme.OpenGLTutorialTheme
import com.yeungeek.opengltutorial.util.FileUtil
import kotlinx.coroutines.*

class MainActivity : ComponentActivity() {

    @OptIn(ExperimentalMaterial3WindowSizeClassApi::class)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            OpenGLTutorialTheme {
                val windowSize = calculateWindowSizeClass(this)
                val displayFeatures = calculateDisplayFeatures(this)

                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    SampleApp { sample ->
                        run {
                            if (sample.id == LocalSampleDataProvider.SAMPLE_EGL) {
                                Log.d("DEBUG", "###### EGL Activity")
                                startActivity(Intent(this, EGLActivity::class.java))
                            } else {
                                startActivity(ShaderDetailActivity.newIntent(this, sample))
                            }
                        }
                    }
                }
            }
        }

        lifecycleScope.launch(Dispatchers.IO) {
            FileUtil.copyAssetsToPrivate(this@MainActivity.applicationContext)
            withContext(Dispatchers.Main) {
                Log.d("Main", "###### copy asset files success")
            }
        }
    }
}

@SuppressLint("UnusedMaterial3ScaffoldPaddingParameter")
@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun SampleApp(navigateToDetail: (Sample) -> Unit) {
    Scaffold(content = {
        SampleListContent(navigateToDetail = navigateToDetail)
    })
}

@Preview(showBackground = true)
@Composable
fun OpenGLTutorialPreview() {
    OpenGLTutorialTheme {
        SampleApp {}
    }
}