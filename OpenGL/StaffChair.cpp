#include "StaffChair.h"
#include "TransformShape.h"
#include "MaterialLib.h"


StaffChair::StaffChair() {

	float h = 0.7f;
	// ngoi
    parts.push_back(
        new TransformShape(
            Translate(0.0f, h, 0.0f) *
            Scale(0.8f, 0.12f, 0.8f),
            new Cube()
        )
    );

    // tua lung
    parts.push_back(
        new TransformShape(
            Translate(0.0f, h + 0.6f, -1.2 * tan(15 / 180 * 3.14) - 0.5f) *
			RotateX(-15) *
            Scale(0.7f, 1.2f, 0.12f),
            new Cube()
        )
    );

	// chan
    parts.push_back(
        new TransformShape(
            Translate(0.0f, h / 2, 0.0f) *
            Scale(0.12f, h, 0.12f),
            new Cube()
        )
    );

    // chan de
    parts.push_back(
        new TransformShape(
            Translate(0.0f, 0, 0.0f) *
            Scale(0.6f, 0.06f, 0.6f),
            new Cube()
        )
    );

    // Star legs (5 legs) — kiểu đơn giản bằng cube; đặt đều quanh trục Y
   

}
StaffChair:: ~StaffChair() {
    for (auto p : parts) {
        delete p;
    }
}

void StaffChair::draw(const mat4& modelMatrix) const {

    for (int i = 0; i < parts.size(); i++) {
        Materials::Wood.apply();
        parts.at(i)->draw(modelMatrix);
    }
}