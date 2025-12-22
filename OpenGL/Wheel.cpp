#include "Wheel.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

Wheel::Wheel(float r) : rotation(0.0f) {

    /* ===== VIỀN BÁNH (ĐEN) ===== */
    rim = new TransformShape(
        RotateX(90) *
        RotateZ(rotation) *
        Scale(r, 0.35f * r, r),      // dày + to
        new Cylinder()
    );

    /* ===== LÕI BÁNH (ĐỎ) ===== */
    core = new TransformShape(
        RotateX(90) *
        RotateZ(rotation) *
        Scale(0.75f * r, 0.32f * r, 0.75f * r),
        new Cylinder()
    );

    
}

Wheel::~Wheel() {
    delete rim;
    delete core;

}

void Wheel::setRotation(float angle) {
    rotation = angle;
}

void Wheel::draw(const mat4& modelMatrix) const {

    /* Viền đen */
    Materials::TireBlack.apply();   // nếu chưa có thì dùng MetalGray tạm
    rim->draw(modelMatrix);

    /* Lõi đỏ */
    Materials::ToyRed.apply();
    core->draw(modelMatrix);

}
