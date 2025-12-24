#include "ToyLocomotive2.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

ToyLocomotive2::ToyLocomotive2(float s) {
    float wheelRadius = 0.48f * s;   // Bán kính bánh xe
    float wheelY = 0.05f * s;        // Chiều cao bánh xe

    // Khung gầm (dài hơn để phù hợp Big Boy)
    chassis = new TransformShape(
        Translate(0.0f, 0.25f * s, 0.0f) *
        Scale(5.2f * s, 0.5f * s, 1.8f * s),
        new Cube()
    );

    // Nồi hơi
    boiler = new TransformShape(
        Translate(-0.8f * s, 1.0f * s, 0.0f) *
        RotateZ(90) *
        Scale(1.1f * s, 3.8f * s, 1.1f * s),
        new Cylinder()
    );

    // Mặt trước
    frontFace = new TransformShape(
        Translate(-2.4f * s, 1.0f * s, 0.0f) *
        RotateZ(90) *
        Scale(1.15f * s, 0.4f * s, 1.15f * s),
        new Cylinder()
    );

    // Mũi tàu
    frontCone = new TransformShape(
        Translate(-2.8f * s, 1.0f * s, 0.0f) *
        RotateZ(-90) *
        Scale(1.15f * s, 0.6f * s, 1.15f * s),
        new Cone()
    );

    // Ống khói
    chimney = new TransformShape(
        Translate(-1.6f * s, 1.8f * s, 0.0f) *
        Scale(0.35f * s, 1.4f * s, 0.35f * s),
        new Cylinder()
    );

    // Tấm chắn khói
    smokeDeflector = new TransformShape(
        Translate(-1.8f * s, 1.4f * s, 0.0f) *
        RotateY(90) *
        Scale(0.15f * s, 1.2f * s, 0.8f * s),
        new Cube()
    );

    // Buồng lái
    cabin = new TransformShape(
        Translate(1.8f * s - 0.10f, 1.2f * s, 0.0f) *
        Scale(1.6f * s, 1.3f * s, 1.8f * s),
        new Cube()
    );

    // Mái cabin
    roof = new TransformShape(
        Translate(1.8f * s - 0.10f, 2.1f * s, 0.0f) *
        Scale(1.7f * s, 0.6f * s, 1.9f * s),
        new TriangularPrism()
    );

    // Toa than
    tender = new TransformShape(
        Translate(3.5f * s, 0.6f * s, 0.0f) *
        Scale(2.8f * s, 1.1f * s, 1.8f * s),
        new Cube()
    );

    // Bánh xe - Cặp phía trước
    wheelFL1 = new TransformShape(Translate(-1.8f * s, wheelY, 0.95f * s), new Wheel(wheelRadius));
    wheelFR1 = new TransformShape(Translate(-1.8f * s, wheelY, -0.95f * s), new Wheel(wheelRadius));
    wheelFL2 = new TransformShape(Translate(-1.0f * s, wheelY, 0.95f * s), new Wheel(wheelRadius));
    wheelFR2 = new TransformShape(Translate(-1.0f * s, wheelY, -0.95f * s), new Wheel(wheelRadius));
    wheelFL3 = new TransformShape(Translate(-0.2f * s, wheelY, 0.95f * s), new Wheel(wheelRadius));
    wheelFR3 = new TransformShape(Translate(-0.2f * s, wheelY, -0.95f * s), new Wheel(wheelRadius));
    wheelFL4 = new TransformShape(Translate(0.6f * s, wheelY, 0.95f * s), new Wheel(wheelRadius));
    wheelFR4 = new TransformShape(Translate(0.6f * s, wheelY, -0.95f * s), new Wheel(wheelRadius));

    // Bánh xe - Cặp phía sau (toa than)
    wheelBL1 = new TransformShape(Translate(2.8f * s, wheelY, 0.95f * s), new Wheel(wheelRadius));
    wheelBR1 = new TransformShape(Translate(2.8f * s, wheelY, -0.95f * s), new Wheel(wheelRadius));
    wheelBL2 = new TransformShape(Translate(3.6f * s, wheelY, 0.95f * s), new Wheel(wheelRadius));
    wheelBR2 = new TransformShape(Translate(3.6f * s, wheelY, -0.95f * s), new Wheel(wheelRadius));
    wheelBL3 = new TransformShape(Translate(4.4f * s, wheelY, 0.95f * s), new Wheel(wheelRadius));
    wheelBR3 = new TransformShape(Translate(4.4f * s, wheelY, -0.95f * s), new Wheel(wheelRadius));
    wheelBL4 = new TransformShape(Translate(5.2f * s, wheelY, 0.95f * s), new Wheel(wheelRadius));
    wheelBR4 = new TransformShape(Translate(5.2f * s, wheelY, -0.95f * s), new Wheel(wheelRadius));
    // Móc nối
    couplerFront = new TransformShape(
        Translate(-3.1f * s + 0.3f, 0.3f * s, 0.0f) *
        Scale(0.4f * s, 0.2f * s, 0.3f * s),
        new Cube()
    );

    couplerBack = new TransformShape(
        Translate(6.0f * s -0.2f, 0.3f * s, 0.0f) *
        Scale(0.4f * s, 0.2f * s, 0.3f * s),
        new Cube()
    );
}

ToyLocomotive2::~ToyLocomotive2() {
    delete chassis;
    delete boiler;
    delete frontFace;
    delete frontCone;
    delete chimney;
    delete smokeDeflector;
    delete cabin;
    delete roof;
    delete tender;

    delete wheelFL1; delete wheelFR1;
    delete wheelFL2; delete wheelFR2;
    delete wheelFL3; delete wheelFR3;
    delete wheelFL4; delete wheelFR4;
    delete wheelBL1; delete wheelBR1;
    delete wheelBL2; delete wheelBR2;
    delete wheelBL3; delete wheelBR3;


    delete couplerFront;
    delete couplerBack;
}

void ToyLocomotive2::draw(const mat4& modelMatrix) const {
    // Vẽ bánh xe
    wheelFL1->draw(modelMatrix); wheelFR1->draw(modelMatrix);
    wheelFL2->draw(modelMatrix); wheelFR2->draw(modelMatrix);
    wheelFL3->draw(modelMatrix); wheelFR3->draw(modelMatrix);
    wheelFL4->draw(modelMatrix); wheelFR4->draw(modelMatrix);
    wheelBL1->draw(modelMatrix); wheelBR1->draw(modelMatrix);
    wheelBL2->draw(modelMatrix); wheelBR2->draw(modelMatrix);
    wheelBL3->draw(modelMatrix); wheelBR3->draw(modelMatrix);


    // Vẽ thân tàu
    Materials::MetalDark.apply();
    chassis->draw(modelMatrix);
    boiler->draw(modelMatrix);
    frontFace->draw(modelMatrix);
    frontCone->draw(modelMatrix);
    chimney->draw(modelMatrix);
    smokeDeflector->draw(modelMatrix);
    couplerFront->draw(modelMatrix);
    couplerBack->draw(modelMatrix);

    Materials::ToyRed.apply();
    cabin->draw(modelMatrix);
    roof->draw(modelMatrix);

    Materials::MetalDark.apply();
    tender->draw(modelMatrix);
}