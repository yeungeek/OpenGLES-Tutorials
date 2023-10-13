//
// Created by jian.yang on 2023/10/12.
//

#include "TransformSample.h"
#include "../../util/GLUtils.h"
#include "../../util/AndroidDebug.h"
#include "../../util/stb_image.h"

namespace Transform {
    GLfloat mVertices[] = {
            //xyz, rgb, st
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };
    GLushort mIndices[] = {
            0, 1, 2,
            0, 2, 3
    };

    TransformSample::TransformSample() {
        LOGD("###### TransformSample init");
        mTexture1Id = 0;
        mTexture2Id = 0;
    }

    TransformSample::~TransformSample() {}

    void TransformSample::OnCreate() {
        char vertexShader[] = "#version 300 es\n"
                              "\n"
                              "layout (location = 0) in vec3 aPos;\n"
                              "layout (location = 1) in vec2 aTexCoord;\n"
                              "\n"
                              "out vec2 TexCoord;\n"
                              "uniform mat4 transform;\n"
                              "\n"
                              "void main() {\n"
                              "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                              "    TexCoord = aTexCoord;\n"
                              "}";

        char fragmentShader[] = "#version 300 es\n"
                                "precision mediump float;\n"
                                "\n"
                                "out vec4 FragColor;\n"
                                "in vec2 TexCoord;\n"
                                "\n"
                                "uniform sampler2D ourTexture;\n"
                                "\n"
                                "void main() {\n"
                                "    FragColor = texture(ourTexture, TexCoord);\n"
                                "}";

        mProgram = GLUtils::CreateProgram(vertexShader, fragmentShader, mVertexShaderId,
                                          mFragmentShaderId);
    }

    void TransformSample::OnDraw(int width, int height) {

    }

    void TransformSample::OnDestroy() {

    }
} // Transform