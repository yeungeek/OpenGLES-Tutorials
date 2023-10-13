//
// Created by jian.yang on 2023/10/12.
//

#ifndef OPENGLES_TUTORIALS_TRANSFORMSAMPLE_H
#define OPENGLES_TUTORIALS_TRANSFORMSAMPLE_H

#include "../BaseSample.h"
#define AWESOMEFACE_PATH BASE_TEXTURES_PATH "awesomeface.png"

namespace Transform {

    class TransformSample : public BaseSample {
    public:
        TransformSample();

        virtual ~TransformSample();

        virtual void OnCreate();

        virtual void OnDraw(int width, int height);

        virtual void OnDestroy();

    private:
        GLuint mTexture1Id,mTexture2Id;
        GLuint mVBO, mEBO, mVAO;
    };

} // Transform

#endif //OPENGLES_TUTORIALS_TRANSFORMSAMPLE_H
