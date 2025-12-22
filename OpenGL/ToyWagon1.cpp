#include "ToyWagon1.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

ToyWagon1::ToyWagon1(float s)
{
    /* ===== KÍCH THƯỚC ===== */
    float length = 3.2f * s;
    float half = length * 0.5f;

    /* ======================================================
       FRONT COUPLER = GỐC LOCAL (0,0,0)
       ====================================================== */

    couplerFront = new TransformShape(
        Translate(0.0f, 0.22f * s, 0.0f) *
        Scale(0.35f * s, 0.14f * s, 0.28f * s),
        new Cube()
    );

    /* ===== ĐẾ TOA ===== */
    base = new TransformShape(
        Translate(half, 0.18f * s, 0.0f) *
        Scale(length, 0.35f * s, 1.6f * s),
        new Cube()
    );

    /* ===== THÀNH TOA (HỞ MUI) ===== */
    float wallH = 0.7f * s;
    float wallT = 0.15f * s;

    sideLeft = new TransformShape(
        Translate(half, wallH / 2 + 0.35f * s, 0.8f * s) *
        Scale(length, wallH, wallT),
        new Cube()
    );

    sideRight = new TransformShape(
        Translate(half, wallH / 2 + 0.35f * s, -0.8f * s) *
        Scale(length, wallH, wallT),
        new Cube()
    );

    sideFront = new TransformShape(
        Translate(half - length / 2 + wallT / 2,
            wallH / 2 + 0.35f * s,
            0.0f) *
        Scale(wallT, wallH, 1.6f * s),
        new Cube()
    );

    sideBack = new TransformShape(
        Translate(half + length / 2 - wallT / 2,
            wallH / 2 + 0.35f * s,
            0.0f) *
        Scale(wallT, wallH, 1.6f * s),
        new Cube()
    );

    /* ===== BÁNH XE ===== */
    float w = 0.42f * s;
    float yWheel = 0.05f * s;

    wheelFL = new TransformShape(
        Translate(half - 1.1f * s, yWheel, 1.0f * s),
        new Wheel(w)
    );

    wheelFR = new TransformShape(
        Translate(half - 1.1f * s, yWheel, -1.0f * s),
        new Wheel(w)
    );

    wheelBL = new TransformShape(
        Translate(half + 1.1f * s, yWheel, 1.0f * s),
        new Wheel(w)
    );

    wheelBR = new TransformShape(
        Translate(half + 1.1f * s, yWheel, -1.0f * s),
        new Wheel(w)
    );

    /* ===== BACK COUPLER ===== */
    couplerBack = new TransformShape(
        Translate(length, 0.22f * s, 0.0f) *
        Scale(0.35f * s, 0.14f * s, 0.28f * s),
        new Cube()
    );
}

ToyWagon1::~ToyWagon1()
{
    delete base;

    delete sideLeft;
    delete sideRight;
    delete sideFront;
    delete sideBack;

    delete wheelFL;
    delete wheelFR;
    delete wheelBL;
    delete wheelBR;

    delete couplerFront;
    delete couplerBack;
}

void ToyWagon1::draw(const mat4& modelMatrix) const
{
    /* ===== BÁNH ===== */
    wheelFL->draw(modelMatrix);
    wheelFR->draw(modelMatrix);
    wheelBL->draw(modelMatrix);
    wheelBR->draw(modelMatrix);

    /* ===== MÓC NỐI ===== */
    Materials::MetalDark.apply();
    couplerFront->draw(modelMatrix);
    couplerBack->draw(modelMatrix);

    /* ===== ĐẾ TOA ===== */
    Materials::ToyRed.apply();
    base->draw(modelMatrix);

    /* ===== THÀNH TOA ===== */
    Materials::ToyGreen.apply();
    sideLeft->draw(modelMatrix);
    sideRight->draw(modelMatrix);
    sideFront->draw(modelMatrix);
    sideBack->draw(modelMatrix);
}
