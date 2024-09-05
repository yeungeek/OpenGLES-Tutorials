//
// Created by jian.yang on 2023/10/5.
//

#include <cstring>
#include "TextureSample.h"
#include "../../util/GLUtils.h"
#include "../../util/AndroidDebug.h"
#include "../../util/stb_image.h"

namespace TextureSample {
    GLfloat mVerticesCoords[] = {
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };

    GLfloat mTextureCoords[] = {
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f
    };

    GLushort mIndices[] = {0, 1, 2,
                           0, 2, 3};

    TextureSample::TextureSample() {
        LOGD("###### TextureSample Init");
        mTextureId = 0;
    }

    TextureSample::~TextureSample() {

    }

    void TextureSample::OnCreate() {
        //shader
        char vertexShader[] = "#version 300 es\n"
                              "\n"
                              "layout (location = 0) in vec3 aPos;\n"
                              "layout (location = 1) in vec2 aTexCoord;\n"
                              "\n"
                              "out vec2 TexCoord;\n"
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

        if (mProgram) {
            mSamplerLoc = glGetUniformLocation(mProgram, "ourTexture");
        }

        int width, height, n;
        unsigned char *data = stbi_load(FACE_PATH, &width, &height, &n, 0);
        LOGD("###### width:%d,height:%d,channel:%d", width, height, n);

        //1. gen texture
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        //2. set filter S = Vertical, T = Horizontal
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glBindTexture(GL_TEXTURE_2D, GL_NONE);


//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, mTextureId);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         data);
        }
        glBindTexture(GL_TEXTURE_2D, GL_NONE);
        stbi_image_free(data);

        glUseProgram(mProgram);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), mVerticesCoords);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), mTextureCoords);
        glEnableVertexAttribArray(1);
    }

    void TextureSample::OnDraw(int width, int height) {
        if (mProgram == 0) {
            return;
        }

        //clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind
        glActiveTexture(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        glUniform1i(mSamplerLoc, 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, mIndices);
    }

    void TextureSample::OnDestroy() {
        glUseProgram(GL_NONE);
        if (mProgram) {
            glDeleteProgram(mProgram);
            mProgram = GL_NONE;
        }
    }
}