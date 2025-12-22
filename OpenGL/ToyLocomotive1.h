#pragma once
#ifndef TOY_LOCOMOTIVE1_H
#define TOY_LOCOMOTIVE1_H

#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Cone.h"
#include "TriangularPrism.h"
#include "Wheel.h"

class ToyLocomotive1 : public Shape {
public:
    ToyLocomotive1(float s = 1.0f);
    ~ToyLocomotive1();

    void draw(const mat4& modelMatrix) const override;

private:
    Shape* chassis;        // khung gầm
    Shape* boiler;         // nồi hơi
    Shape* frontCone;      // mũi tàu
    Shape* chimney;        // ống khói
    Shape* cabin;          // buồng lái
    Shape* roof;           // mái

    Shape* wheelFL;
    Shape* wheelFR;
    Shape* wheelBL;
    Shape* wheelBR;

    Shape* couplerFront;   // móc nối trước

    void initGPUBuffers() override {}
};

#endif
