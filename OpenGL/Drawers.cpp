#include "Drawers.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include <cmath>
#include "Globals.h"
#include "Cylinder.h"

Drawers::Drawers(float _w, float _h, float _d, float _t) {
    // mat day
    t = _t;
    w = _w - 2 * _t;
    h = _h / 4;
    d = _d;

    parts.push_back(
        new TransformShape(
            Scale(w, t, d),
            new Cube()
        )
    );

	// mat ben
    parts.push_back(
        new TransformShape(
            Translate(w / 2 - t / 2, h / 2, 0) *
            Scale(t, h, d),
            new Cube()
        )
    );
    
    parts.push_back(
        new TransformShape(
            Translate(- w / 2 + t / 2, h / 2, 0) *
            Scale(t, h, d),
            new Cube()
        )
    );
	// mat truoc

    frontPos = Translate(0, h / 2, -d / 2);
        
    parts.push_back(
        new TransformShape(
			frontPos  *
            Scale(w, h + 2 * t, t),
            new Cube()
        )
    );

	// tao ngan keo
    parts.push_back(
        new TransformShape(
            frontPos *
			Translate(0, 0, - t) *
            Scale(0.4, 0.05f, t),
            new Cube()
        )
	);

    // o khoa
    lockPos = frontPos * Translate(w / 4, 0, -t / 2);

    parts.push_back(
        new TransformShape(
            RotateX(90) *
        Scale(2 * t, t / 4, 2 * t),
            new Cylinder()
        )
	);
    // chia khoa
    parts.push_back(
        new TransformShape(
            Scale(t/5, t, t),
            new Cube())
    );
    
}
Drawers:: ~Drawers() {
    for (auto p : parts) {
        delete p;
    }
}

void Drawers::draw(const mat4& modelMatrix) const {
    for (int i = 0; i < parts.size() - 2; i++) {
        Materials::Wood.apply();
        parts.at(i)->draw(modelMatrix * Translate(0, 0, -d * drag));
    }
    Materials::Metal.apply();
	parts.at(parts.size() - 1)->draw(modelMatrix * Translate(0, 0, -d * drag)  * lockPos * Translate(0, 0, - t / 2)* RotateZ(twistKey));
    parts.at(parts.size() - 2)->draw(modelMatrix * Translate(0, 0, -d * drag)  * lockPos * RotateZ(twistKey) );
}