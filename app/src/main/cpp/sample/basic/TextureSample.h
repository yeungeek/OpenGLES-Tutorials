//
// Created by jian.yang on 2023/10/5.
//

#ifndef OPENGLES_TUTORIALS_TEXTURESAMPLE_H
#define OPENGLES_TUTORIALS_TEXTURESAMPLE_H

#include "../BaseSample.h"

#define CONTAINER_PATH BASE_TEXTURES_PATH "container.jpg"
namespace TextureSample {
    class TextureSample : public BaseSample {
    public:
        TextureSample();

        virtual ~TextureSample();

        virtual void OnCreate();

        virtual void OnDraw(int width, int height);

        virtual void OnDestroy();

    private:
        GLuint mTextureId;
        GLint mSamplerLoc;
    };
}

#endif //OPENGLES_TUTORIALS_TEXTURESAMPLE_H
