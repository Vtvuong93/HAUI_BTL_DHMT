#pragma once


#include "Shape.h"
#include "Cube.h"
#include <vector>

using std::vector;

typedef vec3 Pos3;

class Door : public Shape {
private:
    vector<Shape*> parts;
    void initGPUBuffers() override {} // Door không có buffer riêng
    float h;
public:
    Door(float w, float h);
    ~Door();

    void draw(const mat4& modelMatrix) const override;

};