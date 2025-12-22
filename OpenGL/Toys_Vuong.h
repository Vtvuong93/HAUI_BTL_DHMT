#pragma once
#ifndef TOYS_H
#define TOYS_H

#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Cone.h"
#include <vector>

// 2. Mô hình Robot đơn giản
class ToyRobot : public Shape {
public:
    ToyRobot();
    ~ToyRobot();
    void draw(const mat4& modelMatrix) const override;
private:
    std::vector<Shape*> parts;
    void initGPUBuffers() override {}
};

#endif