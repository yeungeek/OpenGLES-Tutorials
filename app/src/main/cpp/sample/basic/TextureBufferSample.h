//
// Created by jian.yang on 2023/10/8.
//

#ifndef OPENGLES_TUTORIALS_TEXTUREBUFFERSAMPLE_H
#define OPENGLES_TUTORIALS_TEXTUREBUFFERSAMPLE_H

#include "../BaseSample.h"

namespace TexBuffer {

    class TextureBufferSample : public BaseSample {
    public:
        TextureBufferSample();

        virtual ~TextureBufferSample();

        virtual void OnCreate();

        virtual void OnDraw(int width, int height);

        virtual void OnDestroy();

    private:
        GLuint mTextureId;
        GLuint mVBO, mVAO, mEBO;
    };

} // TexBuffer

#endif //OPENGLES_TUTORIALS_TEXTUREBUFFERSAMPLE_H
