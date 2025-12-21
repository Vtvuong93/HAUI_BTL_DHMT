#pragma once
#ifndef CYCLE_RAIL_H
#define CYCLE_RAIL_H

#include "Shape.h"
#include <vector>

class CycleRail : public Shape {
public:
    CycleRail(float radius = 3.0f, int segments = 80);
    ~CycleRail();

    void draw(const mat4& modelMatrix) const override;

private:
    std::vector<Shape*> rails;

    void initGPUBuffers() override {}
};

#endif
