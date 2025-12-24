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
        steps.push_back(
            new TransformShape(
                Translate(xBase - 1.15, y + 0.75, z) *
                Scale(0.1, 1.5, 0.1),
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
        steps.push_back(
            new TransformShape(
                Translate(x , y + 0.75, z + 1.15) *
                Scale(0.1, 1.5, 0.1),
                new Cube()
            )
		);

        y += stepH;
        x -= stepD;   // rẽ trái
    }

    for (int i = 0; i < secondRun + 5; i++) {
        steps.push_back(
            new TransformShape(
                Translate(x + stepD, y + 0.6, z + 1.5) *
                Scale(0.1, 1.5, 0.1),
                new Cube()
            )
        );
        x += stepD;   // rẽ trái
    }


    lancan.push_back(
        new TransformShape(
            Translate(xBase - 1.15, y - 3.1 , z + 3.5) *
			RotateX(-53.5) *
            Scale(0.2, secondRun * 0.55, 0.15),
            new Cube()
        )
	);

    lancan.push_back(
        new TransformShape(
            Translate(xBase - 3.1, y - 0.1, z + 1.15) *
			RotateZ(-126.5) *
            Scale(0.2, secondRun * 0.55, 0.15),
            new Cube()
        )
    );

    lancan.push_back(
        new TransformShape(
            Translate(-stepD - 0.2, y + 1.3, z + 1.5) *
            RotateZ (90) *
            Scale(0.2, secondRun * 0.7, 0.15),
            new Cube()
        )
    );
}

Stair::~Stair() {
    for (auto s : steps)
        delete s;
}

void Stair::draw(const mat4& modelMatrix) const {
    Materials::MetalDark.apply();
    for (auto s : steps)
        s->draw(modelMatrix);

    Materials::ConcreteBeige.apply();
    for (auto s : lancan)
        s->draw(modelMatrix);
}
