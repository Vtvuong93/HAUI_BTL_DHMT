#pragma once

#ifndef TOY_LOCOMOTIVE4_H
#define TOY_LOCOMOTIVE4_H

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

class ToyLocomotive4 : public Shape {
public:
    ToyLocomotive4(float s = 1.0f);
    ~ToyLocomotive4();
    void draw(const mat4& modelMatrix) const override;

private:
    // Thân tàu chính
    Shape* chassis;         // Khung gầm đen (base)
    Shape* boiler;          // Nồi hơi đen
    Shape* boilerTop;       // Phần trên nồi hơi kem
    Shape* cab;             // Buồng lái kem
    Shape* roof;            // Mái cabin đen
    Shape* dome1;           // Dome lớn (ống khói chính)
    Shape* dome2;           // Dome nhỏ (ống khói phụ)
    Shape* headlight;       // Đèn pha (cam/vàng)
    Shape* runningBoard;    // Bậc thang bạc (chrome)

    // Bánh xe (4 trục - 2 cặp mỗi bên, kiểu cổ điển)
    Shape* wheelFL1, * wheelFR1;
    Shape* wheelFL2, * wheelFR2;
    Shape* wheelBL1, * wheelBR1;
    Shape* wheelBL2, * wheelBR2;

    // Móc nối
    Shape* couplerFront;
    Shape* couplerBack;

    void initGPUBuffers() override {}
};

#endif // TOY_LOCOMOTIVE4_H