#pragma once
#ifndef HOUSE_MODERN_H
#define HOUSE_MODERN_H

#include "Shape.h"
#include "Cube.h"
#include <vector>

class HouseModern : public Shape {
public:
    HouseModern();
    ~HouseModern();

    void draw(const mat4& modelMatrix) const override;

private:
    std::vector<Shape*> parts;

    void initGPUBuffers() override {} // HouseModern không có buffer riêng
};

#endif
