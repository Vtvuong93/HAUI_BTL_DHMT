#ifndef HOUSE_H
#define HOUSE_H

#include "Shape.h"
#include "Cube.h"
#include <vector>

class House : public Shape {
public:
    House();
    ~House();
    void draw(const mat4& modelMatrix) const override;

private:
    std::vector<Shape*> parts;

    void initGPUBuffers() override {} // House không có buffer riêng
};

#endif
