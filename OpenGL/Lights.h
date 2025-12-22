#pragma once
#ifndef LIGHTS_H
#define LIGHTS_H

#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include <vector>

class CeilingLamp : public Shape {
public:
    CeilingLamp();
    ~CeilingLamp();
    // Thêm tham số isOn để biết vẽ đèn sáng hay tối
    void draw(const mat4& modelMatrix, bool isOn) const;

    // Override hàm draw cũ (không dùng đến nhưng phải có để khớp class cha)
    void draw(const mat4& modelMatrix) const override {};

private:
    std::vector<Shape*> wireParts; // Dây treo
    std::vector<Shape*> bulbParts; // Bóng đèn
    void initGPUBuffers() override {}
};

#endif