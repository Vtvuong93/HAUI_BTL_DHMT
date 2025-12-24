#ifndef STAIR_H
#define STAIR_H

#include "Shape.h"
#include "Cube.h"
#include <vector>

using namespace Angel;

class Stair : public Shape {
public:
    Stair(float floorHeight = 6.0f);
    ~Stair();

    void draw(const mat4& modelMatrix) const override;

private:
    std::vector<Shape*> steps;
    std::vector<Shape*> lancan;
    void initGPUBuffers() override {} // Staircase không có buffer riêng
};

#endif
