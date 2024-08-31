//
// Created by yeungeek on 2023/8/21.
//
#include "TriangleSample.h"
#include "../../util/GLUtils.h"
#include "../../util/AndroidDebug.h"

// 逆时针的顶点连接顺序被定义为三角形的正面
//1.arrays
//GLfloat mVertices[] = {
//        -0.5f, -0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//        0.0f, 0.5f, 0.0f
//};
//2. elements
//GLfloat mVertices[] = {
//        0.5f, 0.5f, 0.0f, //top right
//        0.5f, -0.5f, 0.0f,//bottom right
//        -0.5f, -0.5f, 0.0f,//bottom left
//        -0.5f, 0.5f, 0.0f//bottom right
//};

//3.exercise
GLfloat mVertices[] = {
        -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        1.0f, 0.0f, 0.0f
};

GLuint mIndices[] = {
        0, 1, 2 //first
//        0, 2, 3  //second
};

const GLsizei stride = 3 * sizeof(GLfloat);

TriangleSample::TriangleSample() {
    LOGD("###### TriangleSample Init");
}

TriangleSample::~TriangleSample() {

}

void TriangleSample::OnCreate() {
    if (mProgram != 0) {
        return;
    }

    char vertexShader[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec3 vPosition;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vec4(vPosition.x,vPosition.y,vPosition.z,1.0);              \n"
            "}                                        \n";

    char fragmentShader[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
            "}                                            \n";

    mProgram = GLUtils::CreateProgram(vertexShader, fragmentShader, mVertexShaderId,
                                      mFragmentShaderId);

    glUseProgram(mProgram);
    LOGD("###### Program init %d", mProgram);
    //1. use vbo
    //2. use ebo
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);
    //2. use vao
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);

    //load vertex data
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, mVertices);
    //1. vbo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TriangleSample::OnDraw(int width, int height) {
    if (mProgram == 0) {
        return;
    }
    //clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(mProgram);
    //2. use vao TODO
    glBindVertexArray(mVAO);
    //load vertex data
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, mVertices);
//    glEnableVertexAttribArray(0);
    //draw
    //1. vbo
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    //3.ebo

//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//    glDisableVertexAttribArray(0);
}

void TriangleSample::OnDestroy() {
    glUseProgram(GL_NONE);
    if (mProgram) {
        glDeleteProgram(mProgram);
        mProgram = GL_NONE;
    }
    glDeleteBuffers(1, &mVBO);
    glDisableVertexAttribArray(0);
}