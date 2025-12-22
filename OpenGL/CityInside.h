#pragma once
#ifndef CITY_INSIDE_H
#define CITY_INSIDE_H

#include "Shape.h"
#include <vector>

class CityInside : public Shape {
public:
    CityInside(float radius = 2.2f);
    ~CityInside();

    void draw(const mat4& modelMatrix) const override;

private:
    std::vector<Shape*> objects;

    void initGPUBuffers() override {}
};

#endif
