#pragma once
#ifndef TOY_LOCOMOTIVE2_H
#define TOY_LOCOMOTIVE2_H

#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Cone.h"
#include "TriangularPrism.h"
#include "Wheel.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include "Angel.h"

using namespace Angel;

class ToyLocomotive2 : public Shape {
public:
    ToyLocomotive2(float s = 1.0f);
    ~ToyLocomotive2();
    void draw(const mat4& modelMatrix) const override;

private:
    // Thân tàu chính
    Shape* chassis;         // Khung gầm
    Shape* boiler;          // Nồi hơi
    Shape* frontFace;       // Mặt trước
    Shape* frontCone;       // Mũi tàu
    Shape* chimney;         // Ống khói
    Shape* smokeDeflector;  // Tấm chắn khói
    Shape* cabin;           // Buồng lái
    Shape* roof;            // Mái cabin
    Shape* tender;          // Toa than

    // Bánh xe (8 trục - 4 cặp mỗi bên)
    Shape* wheelFL1, * wheelFR1;
    Shape* wheelFL2, * wheelFR2;
    Shape* wheelFL3, * wheelFR3;
    Shape* wheelFL4, * wheelFR4;
    Shape* wheelBL1, * wheelBR1;
    Shape* wheelBL2, * wheelBR2;
    Shape* wheelBL3, * wheelBR3;
    Shape* wheelBL4, * wheelBR4;

    // Móc nối
    Shape* couplerFront;
    Shape* couplerBack;

    void initGPUBuffers() override {}
};

#endif // TOY_LOCOMOTIVE2_H