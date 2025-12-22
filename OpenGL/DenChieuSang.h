#pragma once
#ifndef DENCHIEUSANG_H
#define DENCHIEUSANG_H

#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include <vector>

class DenChieuSang : public Shape {
public:
    DenChieuSang();
    ~DenChieuSang();

    void draw(const Angel::mat4& modelMatrix) const override;

private:
    std::vector<Shape*> parts;
    void initGPUBuffers() override {}
};

#endif