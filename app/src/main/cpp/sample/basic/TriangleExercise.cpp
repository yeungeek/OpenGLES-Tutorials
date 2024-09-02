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


    mProgram = GLUtils::CreateProgram(vertexShader, fragmentShader, mVertexShaderId,
                                      mFragmentShaderId);

    glUseProgram(mProgram);
    LOGD("###### Program init: %d", mProgram);

}

void TriangleExercise::OnDraw(int width, int height) {
    if (mProgram == 0) {
        return;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void TriangleExercise::OnDestroy() {
    if (mProgram != 0) {
        glDeleteProgram(mProgram);
        mProgram = 0;
    }
}