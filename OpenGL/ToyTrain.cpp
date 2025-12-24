#include "ToyTrain.h"
#include <cmath>
#include "Globals.h"
using namespace Angel;

constexpr float PI = 3.14159265359f;

/* =========================================================
   KHỞI TẠO
   ========================================================= */
ToyTrain::ToyTrain(float s)
    : angle(0.0f),
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
#include "Globals.h"   // thêm dòng này

void ToyTrain::draw(const mat4& modelMatrix) const
{
	float targetSpeed1 = 0.005f; 
	float targetSpeed2 = 0.02f;
	float targetSpeed3 = 0.04f;
    /* ================== CẬP NHẬT CHUYỂN ĐỘNG ================== */
    if (g_trainMove) {
        currentSpeed += (targetSpeed1 - currentSpeed) * 0.05f;
        angle += currentSpeed;
    }
    else if (g_TrainMove1) {
        currentSpeed += (targetSpeed2 - currentSpeed) * 0.05f;
		angle += currentSpeed;
    }
    else if (g_TrainMove2) {
        currentSpeed += (targetSpeed3 - currentSpeed) * 0.05f;
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

