#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Shape.h"

class Scene : public Shape {  // Cũng kế thừa Shape để có thể nest hierarchical
public:
    Scene();
    ~Scene();
    void addShape(Shape* shape);  // Phương thức để thêm vật mới
    void draw(const mat4& modelMatrix) const override;

private:
    std::vector<Shape*> shapes;

    void initGPUBuffers() override {}  
};

#endif