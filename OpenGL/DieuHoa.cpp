#include "DieuHoa.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

DieuHoa::DieuHoa() {
    isOn = false;

    // Thân máy
    parts.push_back(
        new TransformShape(
            Scale(2.5f, 0.8f, 0.6f),
            new Cube()
        )
    );

    // Khe gió
    parts.push_back(
        new TransformShape(
            Translate(0, -0.3f, 0.1f) *
            Scale(2.3f, 0.1f, 0.5f),
            new Cube()
        )
    );

    // ?èn báo tr?ng thái
    parts.push_back(
        new TransformShape(
            Translate(1.0f, -0.2f, 0.31f) *
            Scale(0.1f, 0.1f, 0.02f),
            new Cube()
        )
    );
}

DieuHoa::~DieuHoa() {
    for (auto p : parts) delete p;
}

void DieuHoa::toggle() {
    isOn = !isOn;
}

void DieuHoa::draw(const mat4& modelMatrix) const {
    for (size_t i = 0; i < parts.size(); ++i) {

        if (i == 0) {
            Materials::WallPaint.apply();   // Thân
        }
        else if (i == 1) {
            Materials::Metal.apply();       // Khe gió
        }
        else {
            // ?? ?ÈN BÁO ON / OFF
            if (isOn)
                Materials::Ceiling.apply(); // ON
            else
                Materials::RedToy.apply();   // OFF
        }

        parts[i]->draw(modelMatrix);
    }
}
