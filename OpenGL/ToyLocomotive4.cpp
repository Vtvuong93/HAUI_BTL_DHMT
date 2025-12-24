#include "ToyLocomotive4.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

ToyLocomotive4::ToyLocomotive4(float s) {
    float wheelRadius = 0.42f * s;
    float wheelY = 0.05f * s;

    // Khung gầm đen
    chassis = new TransformShape(
        Translate(0.2f, 0.22f * s, 0.0f) *
        Scale(3.2f * s + 0.2f, 0.44f * s, 1.4f * s),
        new Cube()
    );

    // Nồi hơi đen
    boiler = new TransformShape(
        Translate(-0.4f * s, 0.85f * s, 0.0f) *
        RotateZ(90) *
        Scale(0.85f * s, 2.4f * s, 0.85f * s),
        new Cylinder()
    );

    // Phần trên nồi hơi kem (boiler top)
    boilerTop = new TransformShape(
        Translate(-0.4f * s +0.1f, 1.05f * s, 0.0f) *
        RotateZ(90) *
        Scale(0.90f * s + 0.05f, 2.4f * s, 0.90f * s + 0.05f),
        new Cylinder()
    );

    // Buồng lái kem
    cab = new TransformShape(
        Translate(1.2f * s, 1.0f * s, 0.0f) *
        Scale(1.3f * s, 1.4f * s, 1.5f * s),
        new Cube()
    );

    // Mái cabin đen
    roof = new TransformShape(
        Translate(1.2f * s, 1.8f * s, 0.0f) *
        Scale(1.4f * s, 0.4f * s, 1.6f * s),
        new TriangularPrism()
    );

    // Dome lớn (ống khói chính đen)
    dome1 = new TransformShape(
        Translate(-0.6f * s, 1.6f * s, 0.0f) *
        Scale(0.30f * s, 1.1f * s, 0.30f * s),
        new Cylinder()
    );

    // Dome nhỏ (ống khói phụ đen)
    dome2 = new TransformShape(
        Translate(0.0f * s, 1.6f * s, 0.0f) *
        Scale(0.25f * s, 0.8f * s, 0.25f * s),
        new Cylinder()
    );

    // Đèn pha (cam/vàng)
    headlight = new TransformShape(
        Translate(-1.5f * s, 0.85f * s, 0.0f) *
        Scale(0.28f * s, 0.28f * s, 0.28f * s),
        new Cylinder()
    );

    // Bậc thang chạy (running board - bạc/chrome)
    runningBoard = new TransformShape(
        Translate(0.2f, 0.25f * s, 0.0f) *
        Scale(3.2f * s, 0.08f * s, 1.5f * s),
        new Cube()
    );

    // Bánh xe - Cặp trước
    wheelFL1 = new TransformShape(Translate(-0.8f * s, wheelY, 0.85f * s), new Wheel(wheelRadius));
    wheelFR1 = new TransformShape(Translate(-0.8f * s, wheelY, -0.85f * s), new Wheel(wheelRadius));
    wheelFL2 = new TransformShape(Translate(0.6f * s, wheelY, 0.85f * s), new Wheel(wheelRadius));
    wheelFR2 = new TransformShape(Translate(0.6f * s, wheelY, -0.85f * s), new Wheel(wheelRadius));

    // Bánh xe - Cặp sau
    wheelBL1 = new TransformShape(Translate(1.6f * s, wheelY, 0.85f * s), new Wheel(wheelRadius));
    wheelBR1 = new TransformShape(Translate(1.6f * s, wheelY, -0.85f * s), new Wheel(wheelRadius));
    wheelBL2 = new TransformShape(Translate(2.8f * s, wheelY, 0.85f * s), new Wheel(wheelRadius));
    wheelBR2 = new TransformShape(Translate(2.8f * s, wheelY, -0.85f * s), new Wheel(wheelRadius));

    // Móc nối
    couplerFront = new TransformShape(
        Translate(-1.8f * s + 0.1f, 0.25f * s, 0.0f) *
        Scale(0.35f * s, 0.2f * s, 0.3f * s),
        new Cube()
    );

    couplerBack = new TransformShape(
        Translate(3.5f * s -0.1f, 0.25f * s, 0.0f) *
        Scale(0.35f * s, 0.2f * s, 0.3f * s),
        new Cube()
    );
}

ToyLocomotive4::~ToyLocomotive4() {
    delete chassis;
    delete boiler;
    delete boilerTop;
    delete cab;
    delete roof;
    delete dome1;
    delete dome2;
    delete headlight;
    delete runningBoard;

    delete wheelFL1; delete wheelFR1;
    delete wheelFL2; delete wheelFR2;
    delete wheelBL1; delete wheelBR1;
    delete wheelBL2; delete wheelBR2;

    delete couplerFront;
    delete couplerBack;
}

void ToyLocomotive4::draw(const mat4& modelMatrix) const {
    // Vẽ bánh xe
    wheelFL1->draw(modelMatrix); wheelFR1->draw(modelMatrix);
    wheelFL2->draw(modelMatrix); wheelFR2->draw(modelMatrix);
    wheelBL1->draw(modelMatrix); wheelBR1->draw(modelMatrix);
    wheelBL2->draw(modelMatrix); wheelBR2->draw(modelMatrix);

    // Khung gầm đen
    Materials::MetalDark.apply();
    chassis->draw(modelMatrix);
    couplerFront->draw(modelMatrix);
    couplerBack->draw(modelMatrix);

    // Nồi hơi đen
    Materials::MetalDark.apply();
    boiler->draw(modelMatrix);
    dome1->draw(modelMatrix);
    dome2->draw(modelMatrix);

    // Phần trên nồi hơi kem
    Materials::ConcreteBeige.apply();
    boilerTop->draw(modelMatrix);

    // Buồng lái kem
    Materials::ConcreteDark.apply();
    cab->draw(modelMatrix);

    // Mái cabin đen
    Materials::MetalDark.apply();
    roof->draw(modelMatrix);

    // Đèn pha (cam/vàng)
    Materials::LeafGreen.apply();
    headlight->draw(modelMatrix);

    // Bậc thang chạy (bạc/chrome)
    Materials::FabricRed.apply();
    runningBoard->draw(modelMatrix);
}