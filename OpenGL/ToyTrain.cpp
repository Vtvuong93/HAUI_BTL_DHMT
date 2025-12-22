#include "ToyTrain.h"
#include <cmath>

using namespace Angel;

constexpr float PI = 3.14159265359f;

/* =========================================================
   KHỞI TẠO
   ========================================================= */
ToyTrain::ToyTrain(float s)
    : angle(0.0f),
    targetSpeed(0.003f),
    currentSpeed(0.0f),
    scale(s)
{
    locomotive = new TransformShape(mat4(1.0f), new ToyLocomotive(s));
    wagon1 = new TransformShape(mat4(1.0f), new ToyWagon(s));
    wagon2 = new TransformShape(mat4(1.0f), new ToyWagon(s));
    wagon3 = new TransformShape(mat4(1.0f), new ToyWagon(s));

    locoPos = w1Pos = w2Pos = w3Pos = vec3(0.0f, 0.0f, 0.0f);
    locoRotY = w1RotY = w2RotY = w3RotY = 0.0f;
}

/* =========================================================
   HỦY
   ========================================================= */
ToyTrain::~ToyTrain()
{
    delete locomotive;
    delete wagon1;
    delete wagon2;
    delete wagon3;
}

/* =========================================================
   VẼ – SẮP XẾP THEO CUNG TRÒN & QUAY QUANH TÂM
   ========================================================= */
void ToyTrain::draw(const mat4& modelMatrix) const
{
    /* ---------- TỐC ĐỘ QUAY ---------- */
    currentSpeed += (targetSpeed - currentSpeed) * 0.05f;
    angle += currentSpeed;

    /* ---------- THÔNG SỐ HÌNH HỌC ---------- */
    const float R = 3.0f;        // bán kính cung tròn
    const float dTheta = 0.25f;  // độ cong giữa các toa

    /* ---------- HÀM ĐẶT TOA TRÊN CUNG ---------- */
    auto placeOnArc = [&](float theta, vec3& pos, float& rotY)
        {
            pos.x = R * cos(theta);
            pos.z = R * sin(theta);
            rotY = -theta * 180.0f / PI + 90.0f; // tiếp tuyến
        };

    /* ---------- SẮP XẾP ĐẦU TÀU & TOA ---------- */
    float dThetaLoco = 0.18f;  // nhỏ hơn dTheta

    placeOnArc(angle, locoPos, locoRotY);
    placeOnArc(angle - dThetaLoco, w1Pos, w1RotY);
    placeOnArc(angle - dThetaLoco - dTheta, w2Pos, w2RotY);
    placeOnArc(angle - dThetaLoco - 2 * dTheta, w3Pos, w3RotY);

    /* ---------- VẼ ---------- */
    locomotive->draw(modelMatrix * Translate(locoPos) * RotateY(locoRotY));
    wagon1->draw(modelMatrix * Translate(w1Pos) * RotateY(w1RotY));
    wagon2->draw(modelMatrix * Translate(w2Pos) * RotateY(w2RotY));
    wagon3->draw(modelMatrix * Translate(w3Pos) * RotateY(w3RotY));
}
