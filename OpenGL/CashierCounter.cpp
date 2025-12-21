#include "CashierCounter.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include "SetPC.h"

CashierCounter::CashierCounter(float w, float h, float d) {
    float thickness = 0.05f;
    // CashierCounter
    
    // front face
    parts.push_back(
        new TransformShape(
            Translate(0, h / 4 - thickness / 2, d / 2 - thickness / 2) *
            Scale(w - 2 * thickness, h / 2, thickness),
            new Cube()
        )
    );
    // up face
    parts.push_back(
        new TransformShape(
            Translate(0, h/2 , 0) *
            Scale(w, thickness, d),
            new Cube()
        )
    );
    //right leg
    parts.push_back(
        new TransformShape(
            Translate(w / 2  - thickness / 2, 0, 0) *
            Scale(thickness, h - thickness, d),
            new Cube()
        )
    );
    // left leg
    parts.push_back(
        new TransformShape(
            Translate(- w / 2 + thickness / 2, 0, 0) *
            Scale(thickness, h - thickness, d),
            new Cube()
        )
    );

    // ngan ban
    parts.push_back(
        new TransformShape(
            Translate(0, h / 4 - thickness / 2, d * 0.15f - thickness) *
            Scale(w - 2 * thickness, thickness, d / 3 * 2 ),
            new Cube()
        )
    );


    // PC
    parts.push_back(
        new TransformShape(
            Translate(0, h / 2, 0),
            new SetPC(thickness)
        )
    );


}
CashierCounter:: ~CashierCounter() {
    for (auto p : parts) {
        delete p;
    }
}

void CashierCounter::draw(const mat4& modelMatrix) const {
    for (auto p : parts) {
        Materials::Wood.apply();
        p->draw(modelMatrix);
    }
}