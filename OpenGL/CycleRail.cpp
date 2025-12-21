#include "CycleRail.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include "Cube.h"
#include <cmath>

using namespace Angel;

constexpr float PI = 3.14159265359f;

CycleRail::CycleRail(float radius, int segments)
{
    float railLength = 0.25f;
    float railWidth = 0.3f;
    float railHeight = 0.05f;

    float dTheta = 2.0f * PI / segments;

    for (int i = 0; i < segments; i++) {
        float theta = i * dTheta;

        float x = radius * cos(theta);
        float z = radius * sin(theta);

        // Hướng tiếp tuyến của đường tròn
        float rotY = -theta * 180.0f / PI + 90.0f;

        rails.push_back(
            new TransformShape(
                Translate(x, 0.02f, z) *
                RotateY(rotY) *
                Scale(railLength, railHeight, railWidth),
                new Cube()
            )
        );
    }
}

CycleRail::~CycleRail()
{
    for (auto r : rails)
        delete r;
}

void CycleRail::draw(const mat4& modelMatrix) const
{
    Materials::Wood.apply();

    for (auto r : rails)
        r->draw(modelMatrix);
}
