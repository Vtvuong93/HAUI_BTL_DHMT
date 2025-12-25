#pragma once
#ifndef DIEUHOA_H
#define DIEUHOA_H

#include "Shape.h"
#include "Cube.h"
#include <vector>

class DieuHoa : public Shape {
public:
    DieuHoa();
    ~DieuHoa();


    void draw(const Angel::mat4& modelMatrix) const override;
    void toggle(); // Hŕm bat dieu hoa

private:
    std::vector<Shape*> parts;
    bool isOn; // Trang thai 
    float flapAngle;        // góc hi?n t?i c?a cánh
    float flapTargetAngle;  // góc m?c tięu
    void initGPUBuffers() override {}
};

#endif