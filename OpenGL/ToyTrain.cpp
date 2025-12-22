#include "ToyTrain.h"
#include "TransformShape.h"
#include "ToyLocomotive.h"
#include "ToyWagon.h"
#include <cmath>
#include "Globals.h"

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
   VẼ – MÔ HÌNH PHÂN CẤP 
   ========================================================= */
void ToyTrain::draw(const mat4& modelMatrix) const
{
    /* ================== CẬP NHẬT CHUYỂN ĐỘNG ================== */
    if (g_trainMove) {
        currentSpeed += (targetSpeed - currentSpeed) * 0.05f;
        angle += currentSpeed;
    }
    else {
        currentSpeed = 0.0f;
    }

    /* ================== ĐƯỜNG RAY TRÒN ================== */
    const float R = 3.0f;

    vec3 rootPos(
        R * cos(angle),
        0.0f,
        R * sin(angle)
    );

    float rootRotY = -angle * 180.0f / PI + 90.0f;

    /* ================== ROOT TRANSFORM ================== */
    mat4 root =
        modelMatrix *
        Translate(rootPos) *
        RotateY(rootRotY);

    /* ================== VẼ ĐẦU TÀU ================== */
    locomotive->draw(root);

    /* ================== KHOẢNG CÁCH TOA ================== */
    float wagonSpacing = 0.5f;

    /* ================== VẼ TOA (PHÂN CẤP) ================== */
    mat4 w1 = root * Translate(wagonSpacing, 0.0f, 0.0f) * RotateY(20);
    wagon1->draw(w1);

    mat4 w2 = w1 * Translate(1.5f * wagonSpacing, 0.0f, 0.0f) * RotateY(12);
    wagon2->draw(w2);

    mat4 w3 = w2 * Translate(1.55f * wagonSpacing, 0.0f, 0.0f) * RotateY(13);
    wagon3->draw(w3);
}
