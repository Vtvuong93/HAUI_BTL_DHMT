#include "StraightRail.h"
#include "MaterialLib.h"
#include <cmath>
#include "TransformShape.h"
using namespace Angel;

StraightRail::StraightRail(int count, float length, float width, float height)
{
    float spacing = length * 1.5f; // khoảng cách giữa các thanh ray

    for (int i = 0; i < count; i++) {
        float x = i * spacing;

        rails.push_back(
            new TransformShape(
                Translate(x, height / 2.0f, 0.0f) *
                Scale(length, height, width),
                new Cube()
            )
        );
    }
}

StraightRail::~StraightRail()
{
    for (auto r : rails)
        delete r;
}

void StraightRail::draw(const mat4& modelMatrix) const
{
    Materials::Wood.apply(); // Gỗ cho thanh ray

    for (auto r : rails)
        r->draw(modelMatrix);
}
