#include "Stair.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

Stair::Stair(float floorHeight) {

    int totalSteps = 18;
    float stepH = floorHeight / totalSteps;
    float stepD = 0.45f;
    float stepW = 2.5f;

    int firstRun = totalSteps / 2;
    int secondRun = totalSteps - firstRun;

    // ================== VỊ TRÍ CƠ SỞ ==================
    float y = stepH / 2;
    float z = 0.0f;

    // đặt sát mép phải (local space)
    float xBase = stepW / 2;

    // ================== NHÁNH 1
    // từ cửa → đi vào trong nhà (−Z)
    for (int i = 0; i < firstRun; i++) {
        steps.push_back(
            new TransformShape(
                Translate(xBase, y, z) *
                Scale(stepW, stepH, stepD),
                new Cube()
            )
        );
        y += stepH;
        z -= stepD;   // QUAN TRỌNG: đi vào trong
    }

    // ================== CHIẾU NGHỈ
    steps.push_back(
        new TransformShape(
            Translate(xBase, y , z - stepW / 2 + stepD / 4) *
            Scale(stepW, stepH, stepW + stepD/2),
            new Cube()
        )
    );

    // ================== NHÁNH 2
    // rẽ trái → giảm X
    float x = xBase - stepW / 2;
    z -= stepW / 2;

    for (int i = 0; i < secondRun; i++) {
        steps.push_back(
            new TransformShape(
                Translate(x, y, z) *
                Scale(stepD, stepH, stepW),
                new Cube()
            )
        );
        y += stepH;
        x -= stepD;   // rẽ trái
    }
}

Stair::~Stair() {
    for (auto s : steps)
        delete s;
}

void Stair::draw(const mat4& modelMatrix) const {
    Materials::Wood.apply();
    for (auto s : steps)
        s->draw(modelMatrix);
}
