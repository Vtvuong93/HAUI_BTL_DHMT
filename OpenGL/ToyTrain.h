#pragma once
#ifndef TOYTRAIN_H
#define TOYTRAIN_H

#include "Shape.h"
#include "TransformShape.h"
#include "ToyLocomotive.h"
#include "ToyWagon.h"

using namespace Angel;

class ToyTrain : public Shape
{
public:
    ToyTrain(float scale = 1.0f);
    ~ToyTrain();

    void draw(const mat4& modelMatrix) const override;

private:
    /* ===== CÁC PHẦN CỦA TÀU ===== */
    TransformShape* locomotive;
    TransformShape* wagon1;
    TransformShape* wagon2;
    TransformShape* wagon3;

    /* ===== TRẠNG THÁI ===== */
    mutable float angle;        // góc quay chung quanh tâm
    mutable float currentSpeed;

    /* ===== BIẾN HÌNH HỌC ===== */
    mutable vec3  locoPos, w1Pos, w2Pos, w3Pos;
    mutable float locoRotY, w1RotY, w2RotY, w3RotY;

    float scale;

    void initGPUBuffers() override {}
};

#endif // TOYTRAIN_H
