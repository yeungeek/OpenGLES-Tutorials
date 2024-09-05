//
// Created by jian.yang on 2024/9/4.
//

#include "TextureMappingExercise.h"
#include "../../util/GLUtils.h"
#include "../../util/AndroidDebug.h"
#include "../../util/stb_image.h"

namespace TextureBuffer {
    GLfloat mVertices[] = {
            //xyz,st(uv)
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //top right (1,1) -> (1.0)  1-y, flip y
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,    //top left
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,   //bottom left
            0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f     //bottom right
    };

    GLushort mIndices[] = {
            0, 1, 2,
            0, 2, 3
    };

    TextureMappingExercise::TextureMappingExercise() {
        LOGD("###### TextureMappingExercise init");
    }

    TextureMappingExercise::~TextureMappingExercise() {
        LOGD("###### TextureMappingExercise destruct");
    }

    void TextureMappingExercise::OnCreate() {
        char vertexShaderStr[] =
                "#version 300 es\n"
                "layout(location = 0) in vec3 aPos;\n"
                "layout(location = 1) in vec3 aColor;\n"
                "layout(location = 2) in vec2 aTexCoord;\n"
                "out vec3 ourColor;\n"
                "out vec2 TexCoord;\n"
                "void main()\n"
                "{\n"
                "    gl_Position = vec4(aPos, 1.0);\n"
                "    ourColor = aColor;\n"
                "    TexCoord = aTexCoord;\n"
                "}";

        char fragmentShader[] = "#version 300 es\n"
                                "precision mediump float;\n"
                                "out vec4 FragColor;\n"
                                "in vec3 ourColor;\n"
                                "in vec2 TexCoord;\n"
                                "uniform sampler2D ourTexture;\n"
                                "void main() {\n"
                                " FragColor = texture(ourTexture, TexCoord);\n"
                                "}";

        mProgram = GLUtils::CreateProgram(vertexShaderStr, fragmentShader, mVertexShaderId,
                                          mFragmentShaderId);

        //1. texture
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        //2. filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, n;
//        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(FACE_PATH, &width, &height, &n, 0);
        if (data) {
            LOGD("###### width:%d,height:%d,channel:%d", width, height, n);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         data);
        }

        //1.vbo,ebo
        glGenBuffers(1, &mVBO);
        glGenBuffers(1, &mEBO);

        glGenVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);

        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);

        // vertex stride 3+3+2
        // point offset
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                              (void *) (3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                              (void *) (6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        stbi_image_free(data);
        glUseProgram(mProgram);
    }

    void TextureMappingExercise::OnDraw(int width, int height) {
        //clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    }

    void TextureMappingExercise::OnDestroy() {
        glBindTexture(GL_TEXTURE_2D, GL_NONE);
        glUseProgram(GL_NONE);
        if (mProgram) {
            glDeleteProgram(mProgram);
            mProgram = GL_NONE;
        }
    }
}