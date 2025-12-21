#ifndef BALCONY_RAILING_H
#define BALCONY_RAILING_H

#include "Shape.h"
#include "Cube.h"

class BalconyRailing : public Shape {
public:
    BalconyRailing();
    ~BalconyRailing();   // Delete các cube con

    void draw(const mat4& modelMatrix) const override;

private:
    Cube* topBar = nullptr;      // Thanh ngang trên
    Cube* bottomBar = nullptr;   // Thanh ngang dưới
    Cube* pillar = nullptr;      // Cột đứng (dùng chung)

    void initGPUBuffers() override {}  // Không cần buffer riêng
};

#endif
