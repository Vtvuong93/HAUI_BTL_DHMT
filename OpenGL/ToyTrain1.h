#pragma once
#ifndef TOY_TRAIN1_H
#define TOY_TRAIN1_H

#include "Shape.h"

class ToyTrain1 : public Shape {
public:
    ToyTrain1(float s = 1.0f);
    ~ToyTrain1();

    void draw(const mat4& modelMatrix) const override;

private:
    Shape* locomotive;
    Shape* wagon1;
    Shape* wagon2;

    void initGPUBuffers() override {}
};

#endif
