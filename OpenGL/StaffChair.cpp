#include "StaffChair.h"
#include "TransformShape.h"
#include "MaterialLib.h"


StaffChair::StaffChair() {
    // 
    parts.push_back(
        new TransformShape(
            Translate(0, 0, 0) *
            Scale(0, 0, 0),
            new Cube()
        )
    );


}
StaffChair:: ~StaffChair() {
    for (auto p : parts) {
        delete p;
    }
}

void StaffChair::draw(const mat4& modelMatrix) const {
    Materials::Plastic.apply();
    parts.at(0)->draw(modelMatrix);

    for (int i = 1; i < parts.size(); i++) {
        Materials::Metal.apply();
        parts.at(i)->draw(modelMatrix);
    }
}