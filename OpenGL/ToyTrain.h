#ifndef TOY_TRAIN_H
#define TOY_TRAIN_H

#include "Shape.h"

class ToyTrain : public Shape {
public:
    ToyTrain(float s = 1.0f);
    ~ToyTrain();

    void draw(const mat4& modelMatrix) const override;

private:
    // ===== CÁC THÀNH PHẦN (PHÂN CẤP) =====
    Shape* locomotive = nullptr;
    Shape* wagon1 = nullptr;
    Shape* wagon2 = nullptr;
    Shape* wagon3 = nullptr;

    // ===== THAM SỐ CHUYỂN ĐỘNG =====
    mutable float angle;         // góc quay trên ray tròn
    float targetSpeed;           // tốc độ mục tiêu
    mutable float currentSpeed;  // tốc độ hiện tại (làm mượt)
    float scale;                 // tỉ lệ mô hình

    void initGPUBuffers() override {}  // Không cần buffer riêng
};

#endif
