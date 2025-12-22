#pragma once

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
    // ===== Thân tàu =====
    Shape* chassis;         // khung gầm đen dài
    Shape* boiler;          // nồi hơi đen lớn
    Shape* frontFace;       // mặt trước đen
    Shape* frontCone;       // mũi tàu đen + viền đỏ
    Shape* chimney;         // ống khói đen cao
    Shape* smokeDeflector;  // tấm chắn khói (thêm để giống Big Boy)
    Shape* cabin;           // buồng lái đỏ
    Shape* roof;            // mái cabin đỏ
    Shape* tender;          // toa than (thêm để giống hình ảnh)

    // ===== Bánh xe ===== (tăng số lượng để giống Big Boy 4-8-8-4)
    Shape* wheelFL1, * wheelFR1; // cặp 1
    Shape* wheelFL2, * wheelFR2; // cặp 2
    Shape* wheelFL3, * wheelFR3; // cặp 3
    Shape* wheelFL4, * wheelFR4; // cặp 4
    Shape* wheelBL1, * wheelBR1; // cặp 1 sau
    Shape* wheelBL2, * wheelBR2; // cặp 2 sau
    Shape* wheelBL3, * wheelBR3; // cặp 3 sau
    Shape* wheelBL4, * wheelBR4; // cặp 4 sau

    Shape* couplerFront;  // móc nối phía trước
    Shape* couplerBack;   // móc nối phía sau

    void initGPUBuffers() override {}
};