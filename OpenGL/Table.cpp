#include "Table.h"
#include "MaterialLib.h"

Table::Table() {
    top = new Cube();
    leg1 = new Cube();
    leg2 = new Cube();
    leg3 = new Cube();
    leg4 = new Cube();
    // Không cần initGPUBuffers vì các con đã init trong constructor
}

Table::~Table() {
    delete top;
    delete leg1;
    delete leg2;
    delete leg3;
    delete leg4;
}

void Table::draw(const mat4& modelMatrix) const {

    // Mặt bàn — gỗ
    Materials::Wood.apply();
    top->draw(
        modelMatrix *
        Translate(0.0, 0.5, 0.0) *
        Scale(2.0, 0.2, 1.5)
    );

    // Chân bàn — kim loại
    Materials::Metal.apply();

    leg1->draw(modelMatrix * Translate(-0.8, -0.1, -0.6) * Scale(0.2, 1.0, 0.2));
    leg2->draw(modelMatrix * Translate(0.8, -0.1, -0.6) * Scale(0.2, 1.0, 0.2));
    leg3->draw(modelMatrix * Translate(-0.8, -0.1, 0.6) * Scale(0.2, 1.0, 0.2));
    leg4->draw(modelMatrix * Translate(0.8, -0.1, 0.6) * Scale(0.2, 1.0, 0.2));
}
