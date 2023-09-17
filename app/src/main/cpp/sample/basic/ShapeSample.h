//
// Created by jian.yang on 2023/9/15.
//

#ifndef OPENGLES_TUTORIALS_SHAPESAMPLE_H
#define OPENGLES_TUTORIALS_SHAPESAMPLE_H

#include "../BaseSample.h"

class ShapeSample : public BaseSample {
public:
    ShapeSample();
    virtual ~ShapeSample();
    virtual void OnCreate();
    virtual void OnDraw(int width, int height);
    virtual void OnDestroy();
};

#endif //OPENGLES_TUTORIALS_SHAPESAMPLE_H
