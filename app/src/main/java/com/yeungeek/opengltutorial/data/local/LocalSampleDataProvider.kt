package com.yeungeek.opengltutorial.data.local

import com.yeungeek.opengltutorial.data.Sample

object LocalSampleDataProvider {
    private const val SAMPLE_TYPE = 1000
    private const val SAMPLE_TYPE_TRIANGLE = SAMPLE_TYPE + 1
    private const val SAMPLE_TYPE_TRIANGLE_EXERCISE = SAMPLE_TYPE + 1001
    private const val SAMPLE_TYPE_SHAPE_RECTANGLE = SAMPLE_TYPE + 2
    private const val SAMPLE_TYPE_TEXTURE = SAMPLE_TYPE + 3
    private const val SAMPLE_TYPE_TEXTURE_EXERCISE = SAMPLE_TYPE + 2001
    private const val SAMPLE_TYPE_TEXTURE_BUFFER = SAMPLE_TYPE + 4
    private const val SAMPLE_TYPE_TRANSFORM = SAMPLE_TYPE + 5
    private const val SAMPLE_TYPE_COORDINATE = SAMPLE_TYPE + 6
    private const val SAMPLE_TYPE_COORDINATE_EXERCISE = SAMPLE_TYPE + 3001

    const val SAMPLE_EGL = SAMPLE_TYPE + 1000

    val sample = Sample(SAMPLE_TYPE_TRIANGLE, "Triangle", "Basic Triangle")

    val allSamples = listOf(
        Sample(SAMPLE_TYPE_TRIANGLE, "Triangle", "Basic Triangle"),
        Sample(SAMPLE_TYPE_TRIANGLE_EXERCISE, "Triangle", "Triangle Exercise"),
        Sample(SAMPLE_TYPE_SHAPE_RECTANGLE, "Rectangle", "Shape"),
        Sample(SAMPLE_TYPE_TEXTURE, "Texture", "Texture Mapping"),
        Sample(SAMPLE_TYPE_TEXTURE_BUFFER, "Texture Buffer", "Texture Buffer"),
        Sample(SAMPLE_TYPE_TEXTURE_EXERCISE, "Texture Buffer", "Texture Buffer Exercise"),
        Sample(SAMPLE_TYPE_TRANSFORM, "Texture Transform", "Texture mix and transform"),
        Sample(SAMPLE_TYPE_COORDINATE, "Coordinate", "Coordinate system - MVP Matrix"),
        Sample(SAMPLE_TYPE_COORDINATE_EXERCISE, "Coordinate 3D", "Coordinate system - 3D Model"),

        Sample(SAMPLE_EGL, "EGLSample", "EGL")
    )
}