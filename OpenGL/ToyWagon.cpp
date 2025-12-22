#include "ToyWagon.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

ToyWagon::ToyWagon(float s)
{
    /* ===== KHOẢNG CÁCH CHUẨN ===== */
    float length = 3.4f * s;
    float half = length * 0.5f;

    /* ======================================================
       FRONT COUPLER = GỐC LOCAL (0,0,0)
       ====================================================== */

    couplerFront = new TransformShape(
        Translate(0.0f, 0.25f * s, 0.0f) *
        Scale(0.4f * s, 0.15f * s, 0.3f * s),
        new Cube()
    );

    /* ===== ĐẾ TOA (KÉO DÀI VỀ +X) ===== */
    base = new TransformShape(
        Translate(half, 0.15f * s, 0.0f) *
        Scale(length, 0.3f * s, 1.5f * s),
        new Cube()
    );

    /* ===== THÂN TOA ===== */
    body = new TransformShape(
        Translate(half, 0.9f * s, 0.0f) *
        Scale(3.2f * s, 1.1f * s, 1.5f * s),
        new Cube()
    );

    /* ===== MÁI ===== */
    roof = new TransformShape(
        Translate(half, 1.65f * s, 0.0f) *
        Scale(3.3f * s, 0.5f * s, 1.6f * s),
        new TriangularPrism()
    );

    /* ===== BÁNH XE ===== */
    float w = 0.4f * s;
    float yWheel = 0.05f * s;

    wheelFL = new TransformShape(
        Translate(half - 1.2f * s, yWheel, 0.95f * s),
        new Wheel(w)
    );

    wheelFR = new TransformShape(
        Translate(half - 1.2f * s, yWheel, -0.95f * s),
        new Wheel(w)
    );

    wheelBL = new TransformShape(
        Translate(half + 1.2f * s, yWheel, 0.95f * s),
        new Wheel(w)
    );

    wheelBR = new TransformShape(
        Translate(half + 1.2f * s, yWheel, -0.95f * s),
        new Wheel(w)
    );

    /* ===== BACK COUPLER ===== */
    couplerBack = new TransformShape(
        Translate(length, 0.25f * s, 0.0f) *
        Scale(0.4f * s, 0.15f * s, 0.3f * s),
        new Cube()
    );
}

/* ===== HỦY ===== */
ToyWagon::~ToyWagon()
{
    delete base;
    delete body;
    delete roof;

    delete wheelFL;
    delete wheelFR;
    delete wheelBL;
    delete wheelBR;

    delete couplerFront;
    delete couplerBack;
}

/* ===== VẼ ===== */
void ToyWagon::draw(const mat4& modelMatrix) const
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

    /* ===== THÂN TOA ===== */
    Materials::ToyBlue.apply();
    base->draw(modelMatrix);
    body->draw(modelMatrix);

    Materials::ToyYellow.apply();
    roof->draw(modelMatrix);
}
