#include "Tree.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

Tree::Tree(float height) {

    float trunkH = height * 0.5f;
    float leafH = height * 0.6f;

    // Thân cây
    trunk = new TransformShape(
        Translate(0, trunkH / 2, 0) *
        Scale(0.5f, trunkH, 0.5f),
        new Cylinder()
    );

    // Tán cây
    leaf = new TransformShape(
        Translate(0, trunkH + leafH / 2, 0) *
        Scale(2.0f, leafH, 2.0f),
        new Cone()
    );
}

Tree::~Tree() {
    delete trunk;
    delete leaf;
}

void Tree::draw(const mat4& modelMatrix) const {
    Materials::Wood.apply();
    trunk->draw(modelMatrix);

    Materials::LeafGreen.apply();
    leaf->draw(modelMatrix);
}
