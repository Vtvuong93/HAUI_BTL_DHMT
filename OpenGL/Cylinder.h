#pragma once
#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"   // Kế thừa Shape

#define CYLINDER_SLICES 36
// Mỗi slice: 2 tam giác mặt bên (6) + nắp trên (3) + nắp dưới (3) = 12
#define CYLINDER_VERTICES (CYLINDER_SLICES * 12)

class Cylinder : public Shape {
public:
    Cylinder();
    void draw(const mat4& modelMatrix) const override;

private:
    point4 points[CYLINDER_VERTICES];
    color4 colors[CYLINDER_VERTICES];
    vec3   normals[CYLINDER_VERTICES];

    void generateGeometry();
    void initGPUBuffers() override;
};

#endif
