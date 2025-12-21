#include "Chair.h"
#include "MaterialLib.h"
Chair::Chair() {
    seat = new Cube();
    back = new Cube();
    leg1 = new Cube();
    leg2 = new Cube();
    leg3 = new Cube();
    leg4 = new Cube();
}

Chair::~Chair() {
    delete seat;
    delete back;
    delete leg1;
    delete leg2;
    delete leg3;
    delete leg4;
}

void Chair::draw(const mat4& modelMatrix) const {
    Materials::Plastic.apply();
    seat->draw(modelMatrix * Translate(0, 0, 0) * Scale(0.8, 0.1, 0.8));
    back->draw(modelMatrix * Translate(0, 0.3, -0.35) * Scale(0.8, 0.8, 0.1));

    Materials::Wood.apply();
    leg1->draw(modelMatrix * Translate(-0.35, -0.3, -0.35) * Scale(0.1, 0.6, 0.1));
    leg2->draw(modelMatrix * Translate(0.35, -0.3, -0.35) * Scale(0.1, 0.6, 0.1));
    leg3->draw(modelMatrix * Translate(-0.35, -0.3, 0.35) * Scale(0.1, 0.6, 0.1));
    leg4->draw(modelMatrix * Translate(0.35, -0.3, 0.35) * Scale(0.1, 0.6, 0.1));
}
