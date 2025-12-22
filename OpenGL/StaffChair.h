#pragma once

#include "Shape.h"
#include "Cube.h"
#include <vector>

using std::vector;

typedef vec3 Pos3;

class StaffChair : public Shape {
private:
    vector<Shape*> parts;
    void initGPUBuffers() override {} // StaffChair không có buffer riêng
public:
    StaffChair();
    ~StaffChair();
    void draw(const mat4& modelMatrix) const override;
};