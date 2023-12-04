//
// Created by jian.yang on 2023/8/10.
//
#include "stdint.h"
#include <GLES3/gl3.h>

#ifndef OPENGLTUTORIAL_BASESAMPLE_H
#define OPENGLTUTORIAL_BASESAMPLE_H

#define SAMPLE_TYPE 1000
#define SAMPLE_TYPE_TRIANGLE SAMPLE_TYPE + 1
#define SAMPLE_TYPE_SHAPE_RECTANGLE SAMPLE_TYPE + 2
#define SAMPLE_TYPE_TEXTURE SAMPLE_TYPE + 3
#define SAMPLE_TYPE_TEXTURE_BUFFER SAMPLE_TYPE + 4
#define SAMPLE_TYPE_TRANSFORM SAMPLE_TYPE + 5
#define SAMPLE_TYPE_COORDINATE SAMPLE_TYPE + 6

#define BASE_ASSET_PATH "/data/data/com.yeungeek.opengltutorial/files/"
#define BASE_TEXTURES_PATH BASE_ASSET_PATH "textures/"

#define CONTAINER_PATH BASE_TEXTURES_PATH "container.jpg"
#define HEAD_PATH BASE_TEXTURES_PATH "head.png"
#define FACE_PATH BASE_TEXTURES_PATH "face.png"

class BaseSample {
public:
    BaseSample() {
        mProgram = 0;
        mVertexShaderId = 0;
        mFragmentShaderId = 0;
    }

    virtual ~BaseSample() {}

    virtual void OnCreate() = 0;

    virtual void OnDraw(int width, int height) = 0;

    virtual void OnDestroy() = 0;

protected:
    GLuint mProgram;
    GLuint mVertexShaderId;
    GLuint mFragmentShaderId;
};

#endif //OPENGLTUTORIAL_BASESAMPLE_H
