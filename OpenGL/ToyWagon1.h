#pragma once
#ifndef TOY_WAGON1_H
#define TOY_WAGON1_H

#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Cone.h"
#include "TriangularPrism.h"
#include "Wheel.h"

class ToyWagon1 : public Shape {
public:
    ToyWagon1(float s = 1.0f);
    ~ToyWagon1();

    void draw(const mat4& modelMatrix) const override;

private:
    Shape* couplerFront;
    Shape* base;

    Shape* sideLeft;
    Shape* sideRight;
    Shape* sideFront;
    Shape* sideBack;

    Shape* wheelFL;
    Shape* wheelFR;
    Shape* wheelBL;
    Shape* wheelBR;

    Shape* couplerBack;

    void initGPUBuffers() override {}
};

#endif
