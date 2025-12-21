#include "Toys_Vuong.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

// ================== TOY TRAIN ==================
ToyTrain::ToyTrain() {
    // 1. Thân tàu (Hình trụ nằm ngang)
    // Xoay 90 độ quanh Z để hình trụ nằm ngang
    bodyParts.push_back(new TransformShape(Translate(0, 0.2, 0) * RotateZ(90) * Scale(0.3, 0.8, 0.3), new Cylinder()));

    // 2. Khoang lái (Hình hộp phía sau)
    cabinParts.push_back(new TransformShape(Translate(0.25, 0.3, 0) * Scale(0.35, 0.5, 0.35), new Cube()));

    // 3. Ống khói (Hình nón phía trước)
    chimneyParts.push_back(new TransformShape(Translate(-0.25, 0.45, 0) * Scale(0.1, 0.3, 0.1), new Cone()));

    // 4. Bánh xe (4 bánh - Hình trụ dẹt)
    float wheelR = 0.1f; float wheelT = 0.05f;
    // Bánh trước trái/phải
    wheelParts.push_back(new TransformShape(Translate(-0.2, wheelR, 0.15) * RotateX(90) * Scale(wheelR * 2, wheelT, wheelR * 2), new Cylinder()));
    wheelParts.push_back(new TransformShape(Translate(-0.2, wheelR, -0.15) * RotateX(90) * Scale(wheelR * 2, wheelT, wheelR * 2), new Cylinder()));
    // Bánh sau trái/phải
    wheelParts.push_back(new TransformShape(Translate(0.2, wheelR, 0.15) * RotateX(90) * Scale(wheelR * 2, wheelT, wheelR * 2), new Cylinder()));
    wheelParts.push_back(new TransformShape(Translate(0.2, wheelR, -0.15) * RotateX(90) * Scale(wheelR * 2, wheelT, wheelR * 2), new Cylinder()));
}

ToyTrain::~ToyTrain() {
    for (auto p : bodyParts) delete p;
    for (auto p : wheelParts) delete p;
    for (auto p : cabinParts) delete p;
    for (auto p : chimneyParts) delete p;
}

void ToyTrain::draw(const mat4& model) const {
    Materials::ToyRed.apply();
    for (auto p : bodyParts) p->draw(model);

    Materials::ToyBlue.apply();
    for (auto p : cabinParts) p->draw(model);

    Materials::ToyYellow.apply();
    for (auto p : chimneyParts) p->draw(model);

    Materials::ToyBlack.apply();
    for (auto p : wheelParts) p->draw(model);
}

// ================== TOY ROBOT ==================
ToyRobot::ToyRobot() {
    // Thân
    parts.push_back(new TransformShape(Translate(0, 0.3, 0) * Scale(0.3, 0.4, 0.2), new Cube()));
    // Đầu
    parts.push_back(new TransformShape(Translate(0, 0.6, 0) * Scale(0.2, 0.2, 0.2), new Cube()));
    // Chân trái/phải
    parts.push_back(new TransformShape(Translate(-0.1, 0.1, 0) * Scale(0.08, 0.4, 0.08), new Cube()));
    parts.push_back(new TransformShape(Translate(0.1, 0.1, 0) * Scale(0.08, 0.4, 0.08), new Cube()));
    // Tay trái/phải
    parts.push_back(new TransformShape(Translate(-0.2, 0.35, 0) * Scale(0.08, 0.3, 0.08), new Cube()));
    parts.push_back(new TransformShape(Translate(0.2, 0.35, 0) * Scale(0.08, 0.3, 0.08), new Cube()));
}

ToyRobot::~ToyRobot() { for (auto p : parts) delete p; }

void ToyRobot::draw(const mat4& model) const {
    Materials::ToyYellow.apply(); // Robot màu vàng
    for (auto p : parts) p->draw(model);
}