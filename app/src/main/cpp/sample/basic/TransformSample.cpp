//
// Created by jian.yang on 2023/10/12.
//

#include "TransformSample.h"
#include "../../util/GLUtils.h"
#include "../../util/AndroidDebug.h"
#include "../../util/stb_image.h"
#include "../third_party/glm/glm.hpp"
#include "../third_party/glm/gtc/matrix_transform.hpp"
#include "../third_party/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <ctime>

namespace Transform {
    GLfloat mVertices[] = {
            //xyz, st
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
                              "    gl_Position = transform * vec4(aPos, 1.0);\n"
                              "    TexCoord = aTexCoord;\n"
                              "}";

        char fragmentShader[] = "#version 300 es\n"
                                "precision mediump float;\n"
                                "\n"
                                "out vec4 FragColor;\n"
                                "in vec2 TexCoord;\n"
                                "\n"
                                "uniform sampler2D texture1;\n"
                                "uniform sampler2D texture2;\n"
                                "\n"
                                "void main() {\n"
                                "    FragColor = mix(texture(texture1, TexCoord),texture(texture2, TexCoord),0.2);\n"
                                "}";

        mProgram = GLUtils::CreateProgram(vertexShader, fragmentShader, mVertexShaderId,
                                          mFragmentShaderId);
        GLUtils::CheckGLError("###### CreateProgram");
        //1. texture1,texture2
        glGenBuffers(1, &mTexture1Id);
        glBindTexture(GL_TEXTURE_2D, mTexture1Id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);
        int width, height, n;
        unsigned char *data = stbi_load(CONTAINER_PATH, &width, &height, &n, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         data);
        }
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, GL_NONE);

        glGenBuffers(1, &mTexture2Id);
        glBindTexture(GL_TEXTURE_2D, mTexture2Id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        data = stbi_load(FACE_PATH, &width, &height, &n, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         data);
        }
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, GL_NONE);

        //2. vbo,ebo,vao
        glGenBuffers(1, &mVBO);
        glGenBuffers(1, &mEBO);

        glGenBuffers(1, &mVAO);
        glBindVertexArray(mVAO);

        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);

        //3. vertex pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                              (void *) (3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glUseProgram(mProgram); // before setting uniform
        glUniform1i(glGetUniformLocation(mProgram, "texture1"), 0);
        glUniform1i(glGetUniformLocation(mProgram, "texture2"), 1);
    }

    void TransformSample::OnDraw(int width, int height) {
        if (mProgram == 0) {
            return;
        }
        glClear(GL_COLOR_BUFFER_BIT);

        //active
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTexture1Id);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mTexture2Id);

        // transform
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));


        std::time_t currentTime = std::time(0);
        long long timestamp = currentTime * 1;
        trans = glm::rotate(trans, (float) (timestamp % 10), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

        GLint transLoc = glGetUniformLocation(mProgram, "transform");
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(mVAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void *) 0);
    }

    void TransformSample::OnDestroy() {
        glBindTexture(GL_TEXTURE_2D, GL_NONE);
        glUseProgram(GL_NONE);
        if (mProgram) {
            glDeleteProgram(mProgram);
            mProgram = GL_NONE;
        }
    }
} // Transform