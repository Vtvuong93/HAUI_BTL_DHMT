#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
    for (auto shape : shapes) {
        delete shape;
    }
}

void Scene::addShape(Shape* shape) {
    shapes.push_back(shape);
}

void Scene::draw(const mat4& modelMatrix) const {
    for (auto shape : shapes) {
        shape->draw(modelMatrix);  // Áp dụng model chung, hoặc modify nếu cần
    }
}