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
    float pos_x = 0.0, pos_y = 0.0, pos_z = 0.0f;
    float door_w, door_h;

    float thickness = 0.05f;
    // Base

    float base_w = door_w * 1.1f, base_h = 1.0f;
    float base_d = base_h;
    mat4 pos;
public:
    Door(float w, float h, mat4 pos0);
    ~Door();

    void draw(const mat4& modelMatrix) const override;

};