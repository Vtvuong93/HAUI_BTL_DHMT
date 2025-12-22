#include "ToyLocomotive.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

ToyLocomotive::ToyLocomotive(float s) {

    /* ===== Khung gầm đỏ ===== */
    chassis = new TransformShape(
        Translate(0.0f, 0.2f * s, 0.0f) *
        Scale(3.8f * s, 0.35f * s, 1.5f * s),
        new Cube()
    );

    /* ===== Nồi hơi tròn xanh ===== */
    boiler = new TransformShape(
        Translate(-0.6f * s, 0.85f * s, 0.0f) *
        RotateZ(90) *
        Scale(0.85f * s, 2.6f * s, 0.85f * s),
        new Cylinder()
    );

    /* ===== Mặt trước đen ===== */
    frontFace = new TransformShape(
        Translate(-2.0f * s, 0.85f * s, 0.0f) *
        RotateZ(90) *
        Scale(0.9f * s, 0.3f * s, 0.9f * s),
        new Cylinder()
    );

    /* ===== Viền mũi tàu ===== */
    frontCone = new TransformShape(
        Translate(-2.3f * s, 0.85f * s, 0.0f) *
        RotateZ(-90) *
        Scale(0.9f * s, 0.4f * s, 0.9f * s),
        new Cone()
    );

    /* ===== Ống khói ===== */
    chimney = new TransformShape(
        Translate(-1.3f * s, 1.55f * s, 0.0f) *
        Scale(0.28f * s, 1.0f * s, 0.28f * s),
        new Cylinder()
    );

    /* ===== Buồng lái vàng ===== */
    cabin = new TransformShape(
        Translate(1.2f * s, 1.1f * s, 0.0f) *
        Scale(1.5f * s, 1.1f * s, 1.6f * s),
        new Cube()
    );

    /* ===== Mái cabin ===== */
    roof = new TransformShape(
        Translate(1.2f * s, 1.9f * s, 0.0f) *
        Scale(1.6f * s, 0.6f * s, 1.7f * s),
        new TriangularPrism()
    );

    float w = 0.45f * s;                 // bánh lớn
    float yWheel = 0.05f * s;            // nằm dưới khung gầm

    wheelFL = new TransformShape(
        Translate(-1.2f * s, yWheel, 0.95f * s),
        new Wheel(w)
    );

    wheelFR = new TransformShape(
        Translate(-1.2f * s, yWheel, -0.95f * s),
        new Wheel(w)
    );

    wheelBL = new TransformShape(
        Translate(0.6f * s, yWheel, 0.95f * s),
        new Wheel(w)
    );

    wheelBR = new TransformShape(
        Translate(0.6f * s, yWheel, -0.95f * s),
        new Wheel(w)
    );
    couplerBack = new TransformShape(
        Translate(2.1f * s, 0.25f * s, 0.0f) *
        Scale(0.4f * s, 0.15f * s, 0.3f * s),
        new Cube()
    );
}

ToyLocomotive::~ToyLocomotive() {
    delete chassis;
    delete boiler;
    delete frontFace;
    delete frontCone;
    delete chimney;
    delete cabin;
    delete roof;

    delete wheelFL;
    delete wheelFR;
    delete wheelBL;
    delete wheelBR;

    delete couplerBack;
}

void ToyLocomotive::draw(const mat4& modelMatrix) const {

    // ===== BÁNH XE =====
    wheelFL->draw(modelMatrix);
    wheelFR->draw(modelMatrix);
    wheelBL->draw(modelMatrix);
    wheelBR->draw(modelMatrix);

    // ===== THÂN TÀU =====
    Materials::ToyRed.apply();
    chassis->draw(modelMatrix);

    Materials::ToyGreen.apply();
    boiler->draw(modelMatrix);

    Materials::MetalDark.apply();
    frontFace->draw(modelMatrix);
    frontCone->draw(modelMatrix);
    chimney->draw(modelMatrix);

    Materials::ToyYellow.apply();
    cabin->draw(modelMatrix);

    Materials::ToyRed.apply();
    roof->draw(modelMatrix);

    Materials::MetalDark.apply();
    couplerBack->draw(modelMatrix);
}