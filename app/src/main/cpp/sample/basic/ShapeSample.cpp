//
// Created by yeungeek on 2023/9/15.
//
#include "ShapeSample.h"
#include "../../util/GLUtils.h"
#include "../../util/AndroidDebug.h"

GLfloat mShapeVertices[] = {
        0.0f, 0.0f,
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f,
        -0.5f, -0.5f
};

ShapeSample::ShapeSample() {
    LOGD("###### Rectangle Shape");
}

ShapeSample::~ShapeSample() {

}

void ShapeSample::OnCreate() {
    if (mProgram != 0) {
        return;
    }

    char vertexShader[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec3 vPosition;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vec4(vPosition.x,vPosition.y,vPosition.z,1.0);\n"
            "}                                        \n";

    char fragmentShader[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( 1.0, 1.0, 0.0, 1.0 );  \n"
            "}                                            \n";

    mProgram = GLUtils::CreateProgram(vertexShader, fragmentShader, mVertexShaderId,
                                      mFragmentShaderId);

    glUseProgram(mProgram);
    LOGD("###### Program init %d", mProgram);
}

void ShapeSample::OnDraw(int width, int height) {
    if (mProgram == 0) {
        return;
    }

    //clear
    glClear(GL_COLOR_BUFFER_BIT);

    //load vertex data
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, mShapeVertices);
    glEnableVertexAttribArray(0);

    //draw
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

    glDisableVertexAttribArray(0);
}

void ShapeSample::OnDestroy() {
    glUseProgram(GL_NONE);
    if (mProgram) {
        glDeleteProgram(mProgram);
        mProgram = GL_NONE;
    }
}
