#pragma once
#include "Shape.h"
#include "Cube.h"
#include <vector>

class RoadWithTrees : public Shape {
public:
    RoadWithTrees();
    ~RoadWithTrees();

    void draw(const mat4& modelMatrix) const override;

private:
    std::vector<Shape*> parts;

    void initGPUBuffers() override {}
};
