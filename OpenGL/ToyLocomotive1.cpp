#include "ToyLocomotive1.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

ToyLocomotive1::ToyLocomotive1(float s) {

    /* ===== KHUNG GẦM ===== */
    chassis = new TransformShape(
        Translate(0.0f, 0.25f * s, 0.0f) *
        Scale(4.2f * s, 0.4f * s, 1.6f * s),
        new Cube()
    );

    /* ===== NỒI HƠI (TO HƠN) ===== */
    boiler = new TransformShape(
        Translate(-0.4f * s, 1.0f * s, 0.0f) *
        RotateZ(90) *
        Scale(1.0f * s, 3.0f * s, 1.0f * s),
        new Cylinder()
    );

    /* ===== MŨI TÀU NHỌN ===== */
    frontCone = new TransformShape(
        Translate(-2.28f * s, 1.0f * s, 0.0f) *
        RotateZ(90) *
        Scale(1.0f * s, 0.7f * s, 1.0f * s),
        new Cone()
    );

    /* ===== ỐNG KHÓI CAO ===== */
    chimney = new TransformShape(
        Translate(-1.1f * s, 1.f * s, 0.0f) *
        Scale(0.3f * s, 1.3f * s, 0.3f * s),
        new Cylinder()
    );

    /* ===== BUỒNG LÁI (LÙI SAU) ===== */
    cabin = new TransformShape(
        Translate(1.7f * s, 1.05f * s, 0.0f) *
        Scale(1.6f * s, 1.2f * s, 1.7f * s),
        new Cube()
    );

    /* ===== MÁI CONG ===== */
    roof = new TransformShape(
        Translate(1.7f * s, 1.9f * s, 0.0f) *
        Scale(1.7f * s, 0.5f * s, 1.8f * s),
        new TriangularPrism()
    );

    /* ===== BÁNH XE ===== */
    float w = 0.5f * s;
    float yWheel = 0.08f * s;

    wheelFL = new TransformShape(
        Translate(-1.3f * s, yWheel, 1.05f * s),
        new Wheel(w)
    );

    wheelFR = new TransformShape(
        Translate(-1.3f * s, yWheel, -1.05f * s),
        new Wheel(w)
    );

    wheelBL = new TransformShape(
        Translate(0.9f * s, yWheel, 1.05f * s),
        new Wheel(w)
    );

    wheelBR = new TransformShape(
        Translate(0.9f * s, yWheel, -1.05f * s),
        new Wheel(w)
    );

    /* ===== MÓC NỐI TRƯỚC ===== */
    couplerFront = new TransformShape(
        Translate(-1.4f * s, 0.3f * s, 0.0f) *
        Scale(0.45f * s, 0.18f * s, 0.35f * s),
        new Cube()
    );
}

ToyLocomotive1::~ToyLocomotive1() {
    delete chassis;
    delete boiler;
    delete frontCone;
    delete chimney;
    delete cabin;
    delete roof;

    delete wheelFL;
    delete wheelFR;
    delete wheelBL;
    delete wheelBR;

    delete couplerFront;
}

void ToyLocomotive1::draw(const mat4& modelMatrix) const {

    // ===== BÁNH XE =====
    wheelFL->draw(modelMatrix);
    wheelFR->draw(modelMatrix);
    wheelBL->draw(modelMatrix);
    wheelBR->draw(modelMatrix);

    // ===== THÂN TÀU =====
    Materials::ToyBlue.apply();
    chassis->draw(modelMatrix);

    Materials::ToyGreen.apply();
    boiler->draw(modelMatrix);

    Materials::MetalDark.apply();
    frontCone->draw(modelMatrix);
    chimney->draw(modelMatrix);
    couplerFront->draw(modelMatrix);

    Materials::ToyYellow.apply();
    cabin->draw(modelMatrix);

    Materials::ToyRed.apply();
    roof->draw(modelMatrix);
}
