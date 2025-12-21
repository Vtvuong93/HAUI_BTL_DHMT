#pragma once
#ifndef CONE_H
#define CONE_H

#include "Shape.h"   // Kế thừa Shape

#define CONE_SLICES 36
// Mỗi slice: 
// 1 tam giác mặt bên (3) + 1 tam giác đáy (3) = 6 vertices
#define CONE_VERTICES (CONE_SLICES * 6)

class Cone : public Shape {
public:
    Cone();
    void draw(const mat4& modelMatrix) const override;

private:
    point4 points[CONE_VERTICES];
    color4 colors[CONE_VERTICES];
    vec3   normals[CONE_VERTICES];

    void generateGeometry();
    void initGPUBuffers() override;
};

#endif
