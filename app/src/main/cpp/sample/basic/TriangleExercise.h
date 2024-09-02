//
// Created by jian.yang on 2024/8/31.
//

#ifndef OPENGLES_TUTORIALS_TRIANGLEEXERCISE_H
#define OPENGLES_TUTORIALS_TRIANGLEEXERCISE_H

#include "../BaseSample.h"

class TriangleExercise : public BaseSample {
public:
    TriangleExercise();

    virtual ~TriangleExercise();

    virtual void OnCreate();

    virtual void OnDraw(int width, int height);

    virtual void OnDestroy();

private:
//    GLuint mVBO[2], mVAO[2];
};


#endif //OPENGLES_TUTORIALS_TRIANGLEEXERCISE_H
