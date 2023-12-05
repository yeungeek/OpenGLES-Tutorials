//
// Created by jian.yang on 2023/11/27.
//

#include "CoordSystemSample.h"
#include "../../util/AndroidDebug.h"
#include "../../util/GLUtils.h"
#include "../../util/stb_image.h"

namespace CoordSystem {
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

    CoordSystemSample::CoordSystemSample() {
        LOGD("###### CoordSystemSample init");

    }

    CoordSystemSample::~CoordSystemSample() {}

    void CoordSystemSample::OnCreate() {
        if (mProgram) {
            LOGE("###### Coordinate system sample is created");
            return;
        }

        char vertexShader[] = "#version 300 es\n"
                              "layout (location = 0) in vec3 aPos;\n"
                              "layout (location = 1) in vec2 aTexCoord;\n"
                              "out vec2 TexCoord;\n"
                              "void main() {\n"
                              "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                              "    TexCoord = aTexCoord;\n"
                              "}";

        char fragmentShader[] = "#version 300 es\n"
                                "precision mediump float;\n"
                                "out vec4 FragColor;\n"
                                "in vec2 TexCoord;\n"
                                "uniform sampler2D ourTexture;\n"
                                "void main() {\n"
                                "    FragColor = texture(ourTexture, TexCoord);\n"
                                "}";

        mProgram = GLUtils::CreateProgram(vertexShader, fragmentShader, mVertexShaderId,
                                          mFragmentShaderId);

        //1.texture
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        //2.set filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, n;
        // flip y
        stbi_set_flip_vertically_on_load(true);

        unsigned char *data = stbi_load(CONTAINER_PATH, &width, &height, &n, 0);

        if (data) {
            LOGD("###### width:%d,height:%d,channel:%d", width, height, n);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         data);
        }

        //3. VBO,EBO,VAO
        glGenBuffers(1, &mVBO);
        glGenBuffers(1, &mEBO);

        glGenVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);

        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);
        //1.xyz
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) 0);
        glEnableVertexAttribArray(0);

        //2.st  offset = x,y,z 3*4
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                              (void *) (3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        stbi_image_free(data);
        glUseProgram(mProgram);
    }

    void CoordSystemSample::OnDraw(int width, int height) {
        if (mProgram == 0) {
            return;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void *) 0);
    }

    void CoordSystemSample::OnDestroy() {
        glBindTexture(GL_TEXTURE_2D, GL_NONE);
        glUseProgram(GL_NONE);
        if (mProgram) {
            glDeleteProgram(mProgram);
            mProgram = GL_NONE;
        }
    }
}