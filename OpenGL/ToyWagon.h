#pragma once
#include "Shape.h"
#include "Cube.h"
#include "TriangularPrism.h"
#include "Wheel.h"

class ToyWagon : public Shape {
public:
    ToyWagon(float size = 1.0f);
    ~ToyWagon();

    void draw(const mat4& modelMatrix) const override;

private:
    Shape* base;
    Shape* body;
    Shape* roof;

    // ===== BÁNH =====
    Shape* wheelFL;
    Shape* wheelFR;
    Shape* wheelBL;
    Shape* wheelBR;

    // ===== MÓC NỐI =====
    Shape* couplerFront;
    Shape* couplerBack;

    void initGPUBuffers() override {}
};
