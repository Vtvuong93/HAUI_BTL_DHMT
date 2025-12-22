#include "Lights.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

CeilingLamp::CeilingLamp() {
    // 1. Dây treo (Hình trụ nhỏ dài)
    wireParts.push_back(new TransformShape(Translate(0, 0.25, 0) * Scale(0.02, 0.5, 0.02), new Cylinder()));

    // 2. Chụp đèn/Bóng đèn (Hình lập phương hoặc cầu)
    bulbParts.push_back(new TransformShape(Translate(0, 0, 0) * Scale(0.2, 0.2, 0.2), new Cube()));
}

CeilingLamp::~CeilingLamp() {
    for (auto p : wireParts) delete p;
    for (auto p : bulbParts) delete p;
}

void CeilingLamp::draw(const mat4& model, bool isOn) const {
    // Vẽ dây treo (Luôn màu đen)
    Materials::ToyBlack.apply();
    for (auto p : wireParts) p->draw(model);

    // Vẽ bóng đèn (Thay đổi theo trạng thái)
    if (isOn) {
        Materials::LampOn.apply();
    }
    else {
        Materials::LampOff.apply();
    }
    for (auto p : bulbParts) p->draw(model);
}