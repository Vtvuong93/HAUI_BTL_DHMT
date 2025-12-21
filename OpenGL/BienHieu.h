#ifndef BIENHIEU_H
#define BIENHIEU_H

#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include <vector>

class BienHieu : public Shape {
public:
    BienHieu();
    ~BienHieu();

    void draw(const Angel::mat4& modelMatrix) const override;

private:
    std::vector<Shape*> parts;

    void initGPUBuffers() override {} // Không dùng buffer riêng vì dùng l?i t? con
};

#endif