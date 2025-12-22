#pragma once
#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Cone.h"
#include "TriangularPrism.h"
#include "Wheel.h"

class ToyLocomotive : public Shape {
public:
    ToyLocomotive(float size = 1.0f);
    ~ToyLocomotive();

    void draw(const mat4& modelMatrix) const override;

private:
    // ===== Thân tàu =====
    Shape* chassis;      // khung gầm
    Shape* boiler;       // nồi hơi
    Shape* frontFace;    // mặt trước tròn
    Shape* frontCone;    // viền mũi
    Shape* chimney;     // ống khói
    Shape* cabin;       // buồng lái
    Shape* roof;        // mái cabin

    // ===== Bánh xe =====
    Shape* wheelFL;
    Shape* wheelFR;
    Shape* wheelBL;
    Shape* wheelBR;

    Shape* couplerBack;

    void initGPUBuffers() override {}
};
