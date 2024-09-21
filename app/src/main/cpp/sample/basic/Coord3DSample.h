//
// Created by jian.yang on 2024/9/20.
//

#ifndef OPENGLES_TUTORIALS_COORD3DSAMPLE_H
#define OPENGLES_TUTORIALS_COORD3DSAMPLE_H

#include "../BaseSample.h"
#include <detail/type_mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <string>

namespace Coord3D {
    class Coord3DSample : public BaseSample {
    public:
        Coord3DSample();

        virtual void OnCreate();

        virtual void OnDestroy();

        virtual void OnDraw(int width, int height);

        virtual ~Coord3DSample();

        void setMat4(const GLuint &program, const std::string &name, const glm::mat4 &mat);

    private:
        GLuint texture1, texture2;
        glm::mat4 mModel, mView, mProjection;
        GLuint mVBO, mVAO, mEBO;
    };
} // Coord3D

#endif //OPENGLES_TUTORIALS_COORD3DSAMPLE_H
