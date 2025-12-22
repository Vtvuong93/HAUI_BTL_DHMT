#pragma once
#ifndef TOYS_H
#define TOYS_H

#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Cone.h"
#include <vector>

// 1. Mô hình đầu tàu hỏa
class ToyTrain : public Shape {
public:
    ToyTrain();
    ~ToyTrain();
    void draw(const mat4& modelMatrix) const override;
private:
    std::vector<Shape*> bodyParts;   // Thân tàu (Đỏ)
    std::vector<Shape*> wheelParts;  // Bánh xe (Đen)
    std::vector<Shape*> cabinParts;  // Khoang lái (Xanh)
    std::vector<Shape*> chimneyParts;// Ống khói (Vàng)
    void initGPUBuffers() override {}
};

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