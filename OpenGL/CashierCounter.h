#pragma once

#include "Shape.h"
#include "Cube.h"
#include <vector>

using std::vector;

typedef vec3 Pos3;

class CashierCounter : public Shape {
    private:
        vector<Shape*> parts;
        void initGPUBuffers() override {} // CashierCounter không có buffer riêng
    public:
        CashierCounter(float w, float h, float d);
        ~CashierCounter();
        void draw(const mat4& modelMatrix) const override;
};