#ifndef TABLE_H
#define TABLE_H

#include "Shape.h"
#include "Cube.h"

class Table : public Shape {
public:
    Table();
    ~Table();  // Để delete các cube con
    void draw(const mat4& modelMatrix) const override;

private:
    Cube* top = nullptr;  // Mặt bàn
    Cube* leg1 = nullptr; // Chân 1
    Cube* leg2 = nullptr;
    Cube* leg3 = nullptr;
    Cube* leg4 = nullptr;

    void initGPUBuffers() override {}  // Table không cần buffer riêng, dùng của con
};

#endif