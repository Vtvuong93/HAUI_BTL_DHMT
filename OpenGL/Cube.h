#pragma once
#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"  // Kế thừa Shape

class Cube : public Shape {
public:

    Cube();
    void draw(const mat4& modelMatrix) const override;

private:
    point4 points[36];
    color4 colors[36];
    vec3 normals[36];

    void generateGeometry();
    void initGPUBuffers() override;
};

#endif