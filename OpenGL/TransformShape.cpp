#include "TransformShape.h"

TransformShape::TransformShape(const mat4& t, Shape* s)
    : transform(t), shape(s) {
}

TransformShape::~TransformShape() {
    delete shape;
}

void TransformShape::draw(const mat4& parentModel) const {
    mat4 newModel = parentModel * transform;
    shape->draw(newModel);
}
