#include "ToyLocomotive3.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

ToyLocomotive3::ToyLocomotive3(float s) {
    float wheelRadius = 0.40f * s;   // Bánh xe nhỏ hơn, phù hợp đầu máy diesel
    float wheelY = 0.05f * s;        // Chiều cao bánh xe

    // Khung gầm xám (chassis)
    chassis = new TransformShape(
        Translate(0.0f, 0.20f * s, 0.0f) *
        Scale(4.8f * s, 0.40f * s, 1.6f * s),
        new Cube()
    );

    // Thân xe vàng (body)
    body = new TransformShape(
        Translate(0.0f, 0.80f * s, 0.0f) *
        Scale(4.2f * s, 1.0f * s, 1.4f * s),
        new Cube()
    );

    // Buồng lái xám (cab)
    cab = new TransformShape(
        Translate(1.8f * s + 0.2f, 1.4f * s - 0.1f, 0.0f) *
        Scale(1.4f * s + 0.2f, 1.2f * s + 0.1f, 1.5f * s),
        new Cube()
    );

    // Mái xám (roof)
    roof = new TransformShape(
        Translate(1.8f * s + 0.2f, 2.1f * s - 0.05f, 0.0f) *
        Scale(1.5f * s, 0.3f * s, 1.6f * s) * RotateY(90),
        new TriangularPrism()
    );

    // Mũi tàu vàng (nose - hình nón cụt)
    nose = new TransformShape(
        Translate(-2.3f * s, 0.80f * s, 0.0f) *
        RotateZ(90) *
        Scale(0.8f * s, 1.2f * s, 0.8f * s),
        new Cylinder()  // Cylinder với height nhỏ để tạo mũi nhọn
    );

    // Đèn pha (headlight)
    headlight = new TransformShape(
        Translate(-2.4f * s, 0.90f * s, 0.0f) *
        Scale(0.30f * s, 0.30f * s, 0.30f * s),
        new Cylinder()
    );

    // Thanh chắn trước (bumper)
    bumper = new TransformShape(
        Translate(-2.5f * s, 0.25f * s, 0.0f) *
        Scale(0.6f * s, 0.2f * s, 1.5f * s),
        new Cube()
    );

    // Bánh xe - Cặp phía trước
    wheelFL1 = new TransformShape(Translate(-1.4f * s, wheelY, 0.90f * s), new Wheel(wheelRadius));
    wheelFR1 = new TransformShape(Translate(-1.4f * s, wheelY, -0.90f * s), new Wheel(wheelRadius));
    wheelFL2 = new TransformShape(Translate(-0.4f * s, wheelY, 0.90f * s), new Wheel(wheelRadius));
    wheelFR2 = new TransformShape(Translate(-0.4f * s, wheelY, -0.90f * s), new Wheel(wheelRadius));
    wheelFL3 = new TransformShape(Translate(0.6f * s, wheelY, 0.90f * s), new Wheel(wheelRadius));
    wheelFR3 = new TransformShape(Translate(0.6f * s, wheelY, -0.90f * s), new Wheel(wheelRadius));

    // Bánh xe - Cặp phía sau
    wheelBL1 = new TransformShape(Translate(1.6f * s, wheelY, 0.90f * s), new Wheel(wheelRadius));
    wheelBR1 = new TransformShape(Translate(1.6f * s, wheelY, -0.90f * s), new Wheel(wheelRadius));
    wheelBL2 = new TransformShape(Translate(2.6f * s, wheelY, 0.90f * s), new Wheel(wheelRadius));
    wheelBR2 = new TransformShape(Translate(2.6f * s, wheelY, -0.90f * s), new Wheel(wheelRadius));
    wheelBL3 = new TransformShape(Translate(3.6f * s, wheelY, 0.90f * s), new Wheel(wheelRadius));
    wheelBR3 = new TransformShape(Translate(3.6f * s, wheelY, -0.90f * s), new Wheel(wheelRadius));

    // Móc nối
    couplerFront = new TransformShape(
        Translate(-2.6f * s, 0.25f * s, 0.0f) *
        Scale(0.3f * s, 0.2f * s, 0.3f * s),
        new Cube()
    );

    couplerBack = new TransformShape(
        Translate(4.2f * s, 0.25f * s, 0.0f) *
        Scale(0.3f * s, 0.2f * s, 0.3f * s),
        new Cube()
    );
}

ToyLocomotive3::~ToyLocomotive3() {
    delete chassis;
    delete body;
    delete cab;
    delete roof;
    delete nose;
    delete headlight;
    delete bumper;

    delete wheelFL1; delete wheelFR1;
    delete wheelFL2; delete wheelFR2;
    delete wheelFL3; delete wheelFR3;
    delete wheelBL1; delete wheelBR1;
    delete wheelBL2; delete wheelBR2;
    delete wheelBL3; delete wheelBR3;

    delete couplerFront;
    delete couplerBack;
}

void ToyLocomotive3::draw(const mat4& modelMatrix) const {
    // Vẽ bánh xe
    wheelFL1->draw(modelMatrix); wheelFR1->draw(modelMatrix);
    wheelFL2->draw(modelMatrix); wheelFR2->draw(modelMatrix);
    wheelFL3->draw(modelMatrix); wheelFR3->draw(modelMatrix);
    wheelBL1->draw(modelMatrix); wheelBR1->draw(modelMatrix);
    wheelBL2->draw(modelMatrix); wheelBR2->draw(modelMatrix);
    wheelBL3->draw(modelMatrix); wheelBR3->draw(modelMatrix);

    // Vẽ khung gầm xám
    Materials::ConcreteBlue.apply();
    chassis->draw(modelMatrix);

    // Vẽ thân xe vàng
    Materials::ToyYellow.apply();
    body->draw(modelMatrix);
    nose->draw(modelMatrix);

    // Vẽ buồng lái và mái xám
    Materials::MetalGray.apply();
    cab->draw(modelMatrix);

    Materials::ConcreteDark.apply();
    roof->draw(modelMatrix);

    // Đèn pha (trắng)
    Materials::MetalGray.apply();
    headlight->draw(modelMatrix);

    // Thanh chắn trước và móc nối (đen)
    Materials::MetalDark.apply();
    bumper->draw(modelMatrix);
    couplerFront->draw(modelMatrix);
    couplerBack->draw(modelMatrix);
}