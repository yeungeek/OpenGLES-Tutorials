//
// Created by jian.yang on 2023/11/27.
//

#ifndef OPENGLES_TUTORIALS_COORDSYSTEMSAMPLE_H
#define OPENGLES_TUTORIALS_COORDSYSTEMSAMPLE_H

#include "../BaseSample.h"
#include <detail/type_mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

namespace CoordSystem {
    class CoordSystemSample : public BaseSample {
    public:
        CoordSystemSample();

        virtual ~CoordSystemSample();

        virtual void OnCreate();

        virtual void OnDraw(int width, int height);

        virtual void OnDestroy();

        void UpdateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio);

    private:
        GLint mSamplerLoc;
        GLint mMVPMatLoc;
        GLuint mTextureId;
        glm::mat4 mMVPMatrix;
        GLuint mVBO, mVAO, mEBO;
    };
}


#endif //OPENGLES_TUTORIALS_COORDSYSTEMSAMPLE_H
