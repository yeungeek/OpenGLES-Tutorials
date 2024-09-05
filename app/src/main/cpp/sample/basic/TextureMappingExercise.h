//
// Created by jian.yang on 2024/9/4.
//

#ifndef OPENGLES_TUTORIALS_TEXTUREMAPPINGEXERCISE_H
#define OPENGLES_TUTORIALS_TEXTUREMAPPINGEXERCISE_H

#include "../BaseSample.h"

namespace TextureBuffer {
    class TextureMappingExercise : public BaseSample {
    public:
        TextureMappingExercise();

        virtual ~TextureMappingExercise();

        virtual void OnCreate();

        virtual void OnDestroy();

        virtual void OnDraw(int width, int height);

    private:
        GLuint mTextureId;
        GLint mSampleLoc;
        GLuint mVBO, mVAO, mEBO;
    };
}
#endif //OPENGLES_TUTORIALS_TEXTUREMAPPINGEXERCISE_H
