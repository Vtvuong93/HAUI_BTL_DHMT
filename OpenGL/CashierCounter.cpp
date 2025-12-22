#include "CashierCounter.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include "SetPC.h"
#include "Drawers.h"

CashierCounter::CashierCounter(float w, float h, float d) {
    float thickness = 0.05f;
    // CashierCounter
    
    // front face
    parts.push_back(
        new TransformShape(
            Translate(0, 0, d / 2 - thickness / 2) *
            Scale(w - 2 * thickness, h - thickness, thickness),
            new Cube()
        )
    );
    // up face
    parts.push_back(
        new TransformShape(
            Translate(0, h/2 , 0.0f) *
            Scale(w + 0.3f, thickness, d),
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

    // ngan keo
    parts.push_back(
        new TransformShape(
            Translate( - w / 4, h / 5, - thickness / 2) ,
            new Drawers(w / 2, h, d - thickness, thickness)
        )
    );


    // PC
    parts.push_back(
        new TransformShape(
            Translate(w / 4, h / 2, 0),
            new SetPC(thickness)
        )
    );

    // ngan ban

    parts.push_back(
        new TransformShape(
            Translate(0, h/5 - thickness, - thickness / 2) *
            Scale(w - 2 * thickness, thickness, d - thickness),
            new Cube()
        )
    );
    parts.push_back(
        new TransformShape(
            Translate(- thickness / 2,  h/ 2 - h/5 + thickness / 2, - thickness / 2) *
            Scale(thickness, h / 3 + thickness / 4, d - thickness),
            new Cube()
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