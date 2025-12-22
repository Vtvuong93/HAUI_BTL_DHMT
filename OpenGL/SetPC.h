#pragma once


#include "Shape.h"
#include "Cube.h"
#include <vector>

using std::vector;

typedef vec3 Pos3;

class SetPC : public Shape {
private:
    vector<Shape*> parts;
    void initGPUBuffers() override {} // SetPC không có buffer riêng
public:
    SetPC(float t_t);
    ~SetPC();
    void draw(const mat4& modelMatrix) const override;
};