#pragma once
#ifndef HOUSE_MODERN_3F_H
#define HOUSE_MODERN_3F_H

#include "Shape.h"
#include "Cube.h"
#include <vector>

class HouseModern3F : public Shape {
public:
    HouseModern3F();
    ~HouseModern3F();

    void draw(const mat4& modelMatrix) const override;

private:
    std::vector<Shape*> parts;

    // Nhà chỉ là tập hợp các Shape con → không có buffer riêng
    void initGPUBuffers() override {}
};

#endif
