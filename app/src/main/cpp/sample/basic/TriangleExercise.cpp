//
// Created by jian.yang on 2024/8/31.
//

#include "TriangleExercise.h"
#include "../../util/GLUtils.h"
#include "../../util/AndroidDebug.h"

TriangleExercise::TriangleExercise() {
    LOGD("###### TriangleExercise init");
}

TriangleExercise::~TriangleExercise() {
    LOGD("###### TriangleExercise destroy");
}

GLfloat mVertices0[] = {
        -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f
};

GLfloat mVertices1[] = {
        -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f
};

const GLsizei stride = 3 * sizeof(GLfloat);

void TriangleExercise::OnCreate() {
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

    char fragmentShader1[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( 1.0, 1.0, 0.0, 1.0 );  \n"
            "}                                            \n";


    mProgram = GLUtils::CreateProgram(vertexShader, fragmentShader, mVertexShaderId,
                                      mFragmentShaderId);

    mProgram1 = GLUtils::CreateProgram(vertexShader, fragmentShader1, mVertexShaderId,
                                      mFragmentShaderId);

//    glUseProgram(mProgram);
//    glUseProgram(mProgram1);
//    LOGD("###### Program init: %d", mProgram);

    glGenBuffers(2, mVBOs);
    glGenVertexArrays(2, mVAOs);

    glBindVertexArray(mVAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, mVBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices0), mVertices0, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(mVAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, mVBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices1), mVertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,stride,(void *)0);
    glEnableVertexAttribArray(0);
}

void TriangleExercise::OnDraw(int width, int height) {
    if (mProgram == 0) {
        return;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(mProgram);

    glBindVertexArray(mVAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(mProgram1);
    glBindVertexArray(mVAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TriangleExercise::OnDestroy() {
    if (mProgram != 0) {
        glDeleteProgram(mProgram);
        mProgram = 0;
    }

    glDeleteBuffers(2,mVBOs);
    glDeleteBuffers(2,mVAOs);
    glDisableVertexAttribArray(0);
}