#pragma once
#include "Shape.h"
#include "Cone.h"
#include "Cylinder.h"

class Tree : public Shape {
public:
    Tree(float height = 4.0f);
    ~Tree();

    void draw(const mat4& modelMatrix) const override;

private:
    Shape* trunk;
    Shape* leaf;

    void initGPUBuffers() override {}
};
#pragma once
