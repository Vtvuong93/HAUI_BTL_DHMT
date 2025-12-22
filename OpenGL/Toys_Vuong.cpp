#include "Toys_Vuong.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

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