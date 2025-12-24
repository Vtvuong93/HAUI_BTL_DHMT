#include "StraightRail.h"
#include "MaterialLib.h"
#include <cmath>
#include "TransformShape.h"
using namespace Angel;

StraightRail::StraightRail(int count, float length, float width, float height)
{
    float spacing = length * 1.5f; // khoảng cách giữa các thanh ray
	this->count = count;
    for (int i = 0; i < count; i++) {
        float x = i * spacing;

        rails.push_back(
            new TransformShape(
                Translate(x, height / 2.0f, 0.0f) *
                Scale(length, height, width + 0.2),
                new Cube()
            )
        );
    }
    
	float barLength = spacing * (count - 1) + length;

    rails.push_back(
        new TransformShape(
            Translate( 1, height / 2.0f, 0.2f) *
            Scale(barLength, height + 0.1, width / 10),
            new Cube()
        )
    );
    rails.push_back(
        new TransformShape(
            Translate( 1, height / 2.0f, -0.2f) *
            Scale(barLength, height + 0.1, width / 10),
            new Cube()
        )
    );
}

StraightRail::~StraightRail()
{
    for (auto r : rails)
        delete r;
}

void StraightRail::draw(const mat4& modelMatrix) const
{
    Materials::Wood.apply(); // Gỗ cho thanh ray

    for (int i = 0; i < count; i++) rails.at(i)->draw(modelMatrix);

	Materials::MetalDark.apply(); // Kim loại cho thanh nối
	for (int i = count; i < rails.size(); i++) rails.at(i)->draw(modelMatrix);
}
