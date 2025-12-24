#include "CityInside.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include "Cube.h"
#include "Cone.h"
#include <cstdlib>

using namespace Angel;

CityInside::CityInside(float radius)
{

    /* ================== NHÀ (KHỐI HỘP LOẠN) ================== */
    // Các vị trí thủ công, KHÔNG theo vòng
    float housePos[][2] = {
        {-1.4f, -0.6f}, {-0.9f,  0.8f}, { 0.2f, -1.1f},
        { 1.1f, -0.4f}, { 0.7f,  1.0f}, {-0.3f,  0.3f},
        { 1.5f,  0.6f}
    };

    for (int i = 0; i < 7; i++) {
        float x = housePos[i][0];
        float z = housePos[i][1];

        // scale NGẪU NHIÊN NHẸ (dài / ngắn / cao)
        float sx = 0.3f + 0.4f * (i % 3);
        float sy = 0.4f + 0.3f * (i % 2);
        float sz = 0.3f + 0.5f * ((i + 1) % 3);

        objects.push_back(
            new TransformShape(
                Translate(x, sy / 2.0f, z) *
                Scale(sx, sy, sz),
                new Cube()
            )
        );
    }

    /* ================== CÂY (HÌNH NÓN – LOẠN) ================== */
    float treePos[][2] = {
        {-1.6f,  1.2f}, {-0.6f, -1.4f}, { 0.9f,  0.2f},
        { 1.3f, -1.1f}, {-0.2f,  1.5f}
    };

    for (int i = 0; i < 5; i++) {
        float x = treePos[i][0];
        float z = treePos[i][1];

        float h = 0.6f + 0.2f * (i % 2);

        objects.push_back(
            new TransformShape(
                Translate(x, h / 2.0f, z) *
                Scale(0.4f, h, 0.4f),
                new Cone()
            )
        );
    }

    /* ================== VẬT THỂ KHÁC (LOẠN) ================== */
    // Hộp, trụ nhỏ giả lập kho, thùng, công trình phụ
    objects.push_back(
        new TransformShape(
            Translate(-1.0f, 0.15f, 0.1f) *
            Scale(0.2f, 0.3f, 0.2f),
            new Cube()
        )
    );

    objects.push_back(
        new TransformShape(
            Translate(0.4f, 0.1f, -0.5f) *
            Scale(0.15f, 0.2f, 0.4f),
            new Cube()
        )
    );

    objects.push_back(
        new TransformShape(
            Translate(1.0f, 0.2f, 1.3f) *
            Scale(0.25f, 0.5f, 0.25f),
            new Cube()
        )
    );
}

CityInside::~CityInside()
{
    for (auto o : objects)
        delete o;
}

void CityInside::draw(const mat4& modelMatrix) const
{
    for (size_t i = 0; i < objects.size(); i++) {

        if (i == 0) {
            Materials::LeafGreen.apply();   // mặt đất
        }
        else if (i < 8) {
            Materials::ToyRed.apply();     // nhà
        }
        else if (i < 13) {
            Materials::LeafGreen.apply();   // cây
        }
        else {
            Materials::ConcreteDark.apply(); // vật thể phụ
        }

        objects[i]->draw(modelMatrix);
    }
}
