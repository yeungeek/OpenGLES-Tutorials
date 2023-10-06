//
// Created by jian.yang on 2023/10/5.
//

#include "TextureSample.h"
#include "../../util/GLUtils.h"
#include "../../util/AndroidDebug.h"
#include "../../util/stb_image.h"

TextureSample::TextureSample() {
    LOGD("###### TextureSample Init");
}

TextureSample::~TextureSample() {

}

void TextureSample::OnCreate() {
    int x, y, n;
    unsigned char *data = stbi_load(CONTAINER_PATH, &x, &y, &n, 0);

}

void TextureSample::OnDraw(int width, int height) {

}

void TextureSample::OnDestroy() {

}

