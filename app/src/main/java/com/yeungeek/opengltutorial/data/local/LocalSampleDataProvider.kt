package com.yeungeek.opengltutorial.data.local

import com.yeungeek.opengltutorial.data.Sample

object LocalSampleDataProvider {
    const val SAMPLE_TYPE = 1000
    const val SAMPLE_TYPE_TRIANGLE = SAMPLE_TYPE + 1
    const val SAMPLE_TYPE_SHAPE_RECTANGLE = SAMPLE_TYPE + 2
    const val SAMPLE_TYPE_TEXTURE = SAMPLE_TYPE + 3

    val sample = Sample(SAMPLE_TYPE_TRIANGLE, "Triangle", "Basic Triangle")

    val allSamples = listOf(
        Sample(SAMPLE_TYPE_TRIANGLE, "Triangle", "Basic Triangle"),
        Sample(SAMPLE_TYPE_SHAPE_RECTANGLE, "Rectangle", "Shape"),
        Sample(SAMPLE_TYPE_TEXTURE, "Texture", "Texture Mapping"),
    )
}