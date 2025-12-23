#pragma once
#pragma once
#ifndef TOY_LOCOMOTIVE3_H
#define TOY_LOCOMOTIVE3_H

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

class ToyLocomotive3 : public Shape {
public:
    ToyLocomotive3(float s = 1.0f);
    ~ToyLocomotive3();
    void draw(const mat4& modelMatrix) const override;

private:
    // Thân tàu chính
    Shape* chassis;         // Khung gầm xám
    Shape* body;            // Thân xe vàng
    Shape* cab;             // Buồng lái xám
    Shape* roof;            // Mái xám
    Shape* nose;            // Mũi tàu vàng (hình nón cụt)
    Shape* headlight;       // Đèn pha (trắng + viền đen)
    Shape* bumper;          // Thanh chắn trước

    // Bánh xe (6 trục - 3 cặp mỗi bên)
    Shape* wheelFL1, * wheelFR1;
    Shape* wheelFL2, * wheelFR2;
    Shape* wheelFL3, * wheelFR3;
    Shape* wheelBL1, * wheelBR1;
    Shape* wheelBL2, * wheelBR2;
    Shape* wheelBL3, * wheelBR3;

    // Móc nối
    Shape* couplerFront;
    Shape* couplerBack;

    void initGPUBuffers() override {}
};

#endif // TOY_LOCOMOTIVE3_H