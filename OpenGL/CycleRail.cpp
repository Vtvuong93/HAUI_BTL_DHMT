#include "CycleRail.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include "Cube.h"
#include <cmath>

using namespace Angel;

constexpr float PI = 3.14159265359f;

CycleRail::CycleRail(float radius, int segments)
{
    // ================== KÍCH THƯỚC THANH RAY ==================
    float railLength = 0.25f;  // chiều dài thanh ray
    float railWidth = 0.3f;   // chiều ngang thanh ray
    float railHeight = 0.05f;  // chiều cao thanh ray

    // Khoảng cách góc giữa các thanh ray
    float dTheta = 2.0f * PI / segments;

    for (int i = 0; i < segments; i++) {
        float theta = i * dTheta;

        // Tính vị trí x, z theo bán kính vòng tròn
        float x = radius * cos(theta);
        float z = radius * sin(theta);

        // Hướng tiếp tuyến của đường tròn (quay theo Y)
        float rotY = -theta * 180.0f / PI + 90.0f;

        rails.push_back(
            new TransformShape(
                Translate(x, railHeight / 2.0f, z) *  // nâng thanh ray lên mặt đường
                RotateY(rotY) *
                Scale(railLength, railHeight, railWidth),
                new Cube()
            )
        );
    }
}

CycleRail::~CycleRail()
{
    for (auto r : rails)
        delete r;
}

void CycleRail::draw(const mat4& modelMatrix) const
{
    // Áp dụng vật liệu gỗ cho toàn bộ thanh ray
    Materials::Wood.apply();

    for (auto r : rails)
        r->draw(modelMatrix);
}
