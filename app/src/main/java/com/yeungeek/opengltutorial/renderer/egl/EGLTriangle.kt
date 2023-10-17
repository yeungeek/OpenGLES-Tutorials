package com.yeungeek.opengltutorial.renderer.egl

import android.opengl.GLES30
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer

/**
 *  Created by jian.yang on 2023/10/16.
 */
object EGLTriangle {
    private val vertexPoints = floatArrayOf(
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    )

    var vertexBuffer: FloatBuffer

    /**
     * vertex
     */
    private val vertexShader = """#version 300 es
                layout (location = 0) in vec3 vPosition;
                void main() {
                     gl_Position  = vec4(vPosition.x,vPosition.y,vPosition.z,1.0);
                }
                """

    /**
     * fragment
     */
    private val fragmentShader = """#version 300 es
                precision mediump float;
                out vec4 fragColor;
                void main() {
                     fragColor = vec4(1.0,0.0,0.0,1.0);
                }
                """

    init {
        vertexBuffer = ByteBuffer.allocate(vertexPoints.size * 4)
            .order(ByteOrder.nativeOrder()).asFloatBuffer()
    }

    fun initTriangle() {
        GLES30.glClearColor(1f, 1f, 1f, 1f)
        val vertexShaderId = compileShader(GLES30.GL_VERTEX_SHADER, vertexShader)
        val fragmentShaderId = compileShader(GLES30.GL_FRAGMENT_SHADER, fragmentShader)
        GLES30.glUseProgram(linkProgram(vertexShaderId, fragmentShaderId))
    }

    fun draw(width: Int, height: Int) {
        GLES30.glViewport(0, 0, width, height)

        MatrixState.setInitStack()

        GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT)
        val ratio = width * 1.0f / height * 1.0f
        MatrixState.setProjectFrustum(-ratio, ratio, -1f, 1f, 2f, 100f)

        MatrixState.setCamera(0f, 0f, 4f, 0f, 0f, 0f, 0f, 1f, 0f)



        GLES30.glVertexAttribPointer(0, 3, GLES30.GL_FLOAT, false, 0, vertexBuffer)
        GLES30.glEnableVertexAttribArray(0)
        GLES30.glDrawArrays(GLES30.GL_TRIANGLES, 0, 3)
        GLES30.glDisableVertexAttribArray(0)
    }

    private fun compileShader(type: Int, shaderCode: String): Int {
        val shaderId = GLES30.glCreateShader(type)
        if (shaderId != 0) {
            GLES30.glShaderSource(shaderId, shaderCode)
            GLES30.glCompileShader(shaderId)

            val compileStatus = IntArray(1)
            GLES30.glGetShaderiv(shaderId, GLES30.GL_COMPILE_STATUS, compileStatus, 0)
            if (compileStatus[0] == 0) {
                val logInfo = GLES30.glGetShaderInfoLog(shaderId)
                System.err.println(logInfo)
                GLES30.glDeleteShader(shaderId)
                return 0
            }
        }
        return shaderId
    }

    private fun linkProgram(vertexShaderId: Int, fragmentShaderId: Int): Int {
        val programId = GLES30.glCreateProgram()
        return if (programId != 0) {
            GLES30.glAttachShader(programId, vertexShaderId)
            GLES30.glAttachShader(programId, fragmentShaderId)
            GLES30.glLinkProgram(programId)
            val linkStatus = IntArray(1)
            GLES30.glGetProgramiv(programId, GLES30.GL_LINK_STATUS, linkStatus, 0)
            if (linkStatus[0] == 0) {
                val logInfo = GLES30.glGetProgramInfoLog(programId)
                System.err.println(logInfo)
                GLES30.glDeleteProgram(programId)
                return 0
            }
            programId
        } else {
            return 0
        }
    }
}