#ifndef STRAIGHTRAIL_H
#define STRAIGHTRAIL_H

#include "Shape.h"
#include "Cube.h"
#include <vector>

class StraightRail : public Shape {
public:
    StraightRail(int count = 10, float length = 0.15f, float width = 0.3f, float height = 0.05f);
    ~StraightRail();

    void draw(const mat4& modelMatrix) const override;

private:
    std::vector<Shape*> rails;  // Các thanh ray nối tiếp

    void initGPUBuffers() override {} // StraightRail không cần buffer riêng
	int count;
};

#endif
