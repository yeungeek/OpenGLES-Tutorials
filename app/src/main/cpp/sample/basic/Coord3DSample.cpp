//
// Created by jian.yang on 2024/9/20.
//

#include "Coord3DSample.h"
#include "../../util/AndroidDebug.h"
#include "../../util/GLUtils.h"
#include "../../util/stb_image.h"

namespace Coord3D {

    GLfloat mVertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    Coord3DSample::Coord3DSample() {
        LOGD("###### CoordSystemSample init");
    }

    Coord3DSample::~Coord3DSample() {}

    void Coord3DSample::OnCreate() {
        if (mProgram) {
            LOGE("###### Coord3DSample system sample is created");
            return;
        }

        char vertexShader[] = "#version 300 es\n"
                              "layout (location = 0) in vec3 aPos;\n"
                              "layout (location = 1) in vec2 aTexCoord;\n"
                              "out vec2 TexCoord;\n"
                              "uniform mat4 model;\n"
                              "uniform mat4 view;\n"
                              "uniform mat4 projection;\n"
                              "void main() {\n"
                              "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
                              "    TexCoord = aTexCoord;\n"
                              "}";

        char fragmentShader[] = "#version 300 es\n"
                                "precision mediump float;\n"
                                "out vec4 FragColor;\n"
                                "in vec2 TexCoord;\n"
                                "uniform sampler2D texture1;\n"
                                "uniform sampler2D texture2;\n"
                                "void main() {\n"
                                "    FragColor = mix(texture(texture1, TexCoord),texture(texture2, TexCoord),0.2);\n"
                                "}";

        mProgram = GLUtils::CreateProgram(vertexShader, fragmentShader, mVertexShaderId,
                                          mFragmentShaderId);

        //TODO depth
        glEnable(GL_DEPTH_TEST);

        //1. texture1
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);

        //2. filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //load img
        int width, height, n;

        unsigned char *data = stbi_load(CONTAINER_PATH, &width, &height, &n, 0);
        if (data) {
            LOGD("###### load data, width:%d,height:%d,channel:%d", width, height, n);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         data);
        }
        stbi_image_free(data);

        //2. texture2
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(FACE_PATH, &width, &height, &n, 0);
        if (data) {
            LOGD("###### load texture2, width:%d,height:%d,channel:%d", width, height, n);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         data);
        }
        stbi_image_free(data);

        //3. vao,buffer
        glGenVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);

        glGenBuffers(1, &mVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                              (void *) (3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glUseProgram(mProgram);
        GLint l1 = glGetUniformLocation(mProgram, "texture1");
        GLint l2 = glGetUniformLocation(mProgram, "texture2");

        glUniform1i(l1, 0);
        glUniform1i(l2, 1);
    }

    void Coord3DSample::OnDraw(int width, int height) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //create transform
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        std::time_t currentTime = std::time(0);
        long long timestamp = currentTime * 1;

        model = glm::rotate(model, (float) (timestamp % 10) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.0f, -6.0f));
        projection = glm::perspective(glm::radians(45.0f), width / (float) height, 0.1f, 100.0f);

        setMat4(mProgram, "model", model);
        setMat4(mProgram, "view", view);
        setMat4(mProgram, "projection", projection);

        glBindVertexArray(mVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Coord3DSample::OnDestroy() {
        glBindTexture(GL_TEXTURE_2D, GL_NONE);
        glUseProgram(GL_NONE);
        if (mProgram) {
            glDeleteProgram(mProgram);
            mProgram = GL_NONE;
        }
        glDeleteVertexArrays(1, &mVAO);
        glDeleteBuffers(1, &mVBO);
    }

    void Coord3DSample::setMat4(const GLuint &program, const std::string &name,
                                const glm::mat4 &mat) {
        glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
} // Coord3D