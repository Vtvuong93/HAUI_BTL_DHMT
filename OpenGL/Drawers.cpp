#include "Drawers.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include <cmath>
#include "Globals.h"

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

    //
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
    parts.push_back(
        new TransformShape(
            Translate(0, h / 2, -d / 2) *
            Scale(w, h + 2 * t, t),
            new Cube()
        )
    );
    
}
Drawers:: ~Drawers() {
    for (auto p : parts) {
        delete p;
    }
}

void Drawers::draw(const mat4& modelMatrix) const {
    for (auto &p : parts) {
        Materials::Wood.apply();
        p->draw(modelMatrix * Translate(0, 0, -d * drag));
    }
}