//
// Created by jian.yang on 2023/11/27.
//

#include "CoordSystemSample.h"
#include "../../util/AndroidDebug.h"
#include "../../util/GLUtils.h"
#include "../../util/stb_image.h"

namespace CoordSystem {
    GLfloat mVertices[] = {
            -0.5f, 0.5f, 0.0f,  // Position 0
            -0.5f, -0.5f, 0.0f,  // Position 1
            0.5f, -0.5f, 0.0f,  // Position 2
            0.5f, 0.5f, 0.0f // Position 3
    };

    GLfloat mTextureCoords[] = {
            0.0f, 0.0f,        // TexCoord 0
            0.0f, 1.0f,        // TexCoord 1
            1.0f, 1.0f,        // TexCoord 2
            1.0f, 0.0f         // TexCoord 3
    };

    GLfloat mIndices[] = {
            0, 1, 2,
            0, 2, 3
    };

    CoordSystemSample::CoordSystemSample() {
        LOGD("###### CoordSystemSample init");
        mSamplerLoc = GL_NONE;
        mMVPMatLoc = GL_NONE;
    }

    CoordSystemSample::~CoordSystemSample() {}

    void CoordSystemSample::OnCreate() {
        if (mProgram) {
            LOGE("###### Coordinate system sample is created");
            return;
        }

        char vertexShader[] = "#version 300 es\n"
                              "\n"
                              "layout(location = 0) in vec3 aPos;\n"
                              "layout(location = 1) in vec2 aTexCoord;\n"
                              "\n"
                              "uniform mat4 uMVPMatrix;\n"
                              "out vec2 vTexCoord;\n"
                              "\n"
                              "void main() {\n"
                              "    gl_Position = vec4(aPos,1.0);\n"
                              "    vTexCoord = aTexCoord;\n"
                              "}";

        char fragmentShader[] = "#version 300 es\n"
                                "precision mediump float;\n"
                                "in vec2 vTexCoord;\n"
                                "layout (location = 0) out vec4 vFragColor;\n"
                                "uniform sampler2D sTextureMap;\n"
                                "\n"
                                "void main() {\n"
                                "    vFragColor = texture(sTextureMap, vTexCoord);\n"
                                "}";

        mProgram = GLUtils::CreateProgram(vertexShader, fragmentShader, mVertexShaderId,
                                          mFragmentShaderId);
        GLUtils::CheckGLError("###### CreateProgram");

        if (mProgram) {
            mSamplerLoc = glGetUniformLocation(mProgram, "sTextureMap");
            mMVPMatLoc = glGetUniformLocation(mProgram, "uMVPMatrix");
        }

        // Texture
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, GL_NONE);


        // Create VBO
        glGenBuffers(3, mVBOIds);
        glBindBuffer(GL_ARRAY_BUFFER, mVBOIds[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, mVBOIds[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(mTextureCoords), mTextureCoords, GL_STATIC_DRAW);

        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBOIds[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);

        // VAO
        glGenVertexArrays(1, &mVAOId);
        glBindVertexArray(mVAOId);

        glBindBuffer(GL_ARRAY_BUFFER, mVBOIds[0]);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
        glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

        glBindBuffer(GL_ARRAY_BUFFER, mVBOIds[1]);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *) 0);
        glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBOIds[2]);

        glBindVertexArray(GL_NONE);

        // load image
        int width, height, n;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(CONTAINER_PATH, &width, &height, &n, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        if (data) {
            LOGD("##### load image success!");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNALED, data);
        }
        glBindTexture(GL_TEXTURE_2D, GL_NONE);

        stbi_image_free(data);
        glUseProgram(mProgram);
    }

    void CoordSystemSample::OnDraw(int width, int height) {
        if (mProgram == 0) {
            return;
        }
        glClear(GL_COLOR_BUFFER_BIT);

//        UpdateMVPMatrix(mMVPMatrix, 0, 0, (float) width / height);
        // MVP matrix

        glUseProgram(mProgram);
        glBindVertexArray(mVAOId);

//        glUniformMatrix4fv(mMVPMatLoc, 1, GL_FALSE, &mMVPMatrix[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        glUniform1i(mSamplerLoc, 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void *) 0);
    }

    void CoordSystemSample::OnDestroy() {
        glBindTexture(GL_TEXTURE_2D, GL_NONE);
        glUseProgram(GL_NONE);
        if (mProgram) {
            glDeleteProgram(mProgram);
            mProgram = GL_NONE;
        }
    }

    void CoordSystemSample::UpdateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY,
                                            float ratio) {
//        LOGD("###### UpdateMVPMatrix: angleX = %d, angleY = %d, ratio = %f", angleX, angleY, ratio);

        angleX = angleX % 360;
        angleY = angleY % 360;

        // change to radians
        float radiansX = static_cast<float>(MATH_PI / 180 * angleX);
        float radiansY = static_cast<float>(MATH_PI / 180 * angleY);

        //Projection Matrix
        glm::mat4 projection = glm::perspective(45.0f, ratio, 0.1f, 100.0f);

        //View Matrix
        glm::mat4 view = glm::lookAt(
                glm::vec3(0, 0, 4),
                glm::vec3(0, 0, 0),
                glm::vec3(0, 1, 0)
        );

        //Model Matrix
        glm::mat4 model = glm::mat4(1.0f);
        //scale
        model = glm::rotate(model, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

        mvpMatrix = projection * view * model;
    }
}