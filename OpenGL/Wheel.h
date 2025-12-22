#pragma once
#include "Shape.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Cube.h"

class Wheel : public Shape {
public:
    Wheel(float r);
    ~Wheel();

    void draw(const mat4& modelMatrix) const override;
    void setRotation(float angle);

private:
    Shape* rim;    // viền đen
    Shape* core;   // lõi đỏ
    float rotation;

    void initGPUBuffers() override {}
};
