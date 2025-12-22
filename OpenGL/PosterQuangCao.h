#pragma once
#ifndef POSTERQUANGCAO_H
#define POSTERQUANGCAO_H

#include "Shape.h"
#include "Cube.h"
#include <vector>

class PosterQuangCao : public Shape {
public:
    PosterQuangCao();
    ~PosterQuangCao();

    void draw(const Angel::mat4& modelMatrix) const override;

private:
    std::vector<Shape*> parts;
    void initGPUBuffers() override {}
};

#endif