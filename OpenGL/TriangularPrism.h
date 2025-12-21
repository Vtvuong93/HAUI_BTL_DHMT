#pragma once
#ifndef TRIANGULAR_PRISM_H
#define TRIANGULAR_PRISM_H

#include "Shape.h"

class TriangularPrism : public Shape {
public:
    TriangularPrism();
    void draw(const mat4& modelMatrix) const override;

private:
    // 18 tam giác → 54 đỉnh
    point4 points[54];
    color4 colors[54];
    vec3   normals[54];

    void generateGeometry();
    void initGPUBuffers() override;
};

#endif
