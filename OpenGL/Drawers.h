#pragma once

#include "Shape.h"
#include "Cube.h"
#include <vector>

using std::vector;

typedef vec3 Pos3;

class Drawers : public Shape {
private:
    vector<Shape*> parts;
    void initGPUBuffers() override {} // Drawers không có buffer riêng
    mat4 lockPos, frontPos;
    float w, h, t, d;
public:
    Drawers(float _w, float _h, float _d, float _t);
    ~Drawers();
    void draw(const mat4& modelMatrix) const override;
};