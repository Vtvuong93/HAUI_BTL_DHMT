#include "Road.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include "Tree.h"

using namespace Angel;

RoadWithTrees::RoadWithTrees() {

    float roadW = 30.0f;
    float roadL = 60.0f;
    float roadT = 0.2f;

    float sidewalkW = 30.0f;
    float sidewalkH = 0.15f;

    // ================== VỈA HÈ TRÁI ==================
    parts.push_back(
        new TransformShape(
            Translate(-(roadW / 2 + sidewalkW / 2),
                sidewalkH / 2,
                0) *
            Scale(sidewalkW,
                sidewalkH,
                roadL),
            new Cube()
        )
    );

    // ================== VỈA HÈ PHẢI ==================
    parts.push_back(
        new TransformShape(
            Translate((roadW / 2 + sidewalkW / 2),
                sidewalkH / 2,
                0) *
            Scale(sidewalkW,
                sidewalkH,
                roadL),
            new Cube()
        )
    );

    // ================== MẶT ĐƯỜNG ==================
    parts.push_back(
        new TransformShape(
            Translate(0, roadT / 2, 0) *
            Scale(roadW, roadT, roadL),
            new Cube()
        )
    );

    // ================== VẠCH KẺ (TRẮNG NGÀ) ==================
    float dashL = 3.0f;
    float gap = 4.0f;   // giãn hơn cho thoáng

    for (float z = -roadL / 2 + dashL; z < roadL / 2; z += dashL + gap) {
        parts.push_back(
            new TransformShape(
                Translate(0, roadT + 0.01f, z) *
                Scale(0.4f, 0.05f, dashL),
                new Cube()
            )
        );
    }

    // ================== HÀNG CÂY (THƯA HƠN) ==================
    for (float z = -roadL / 2 + 6.0f; z < roadL / 2; z += 15.0f) {

        // Trái
        parts.push_back(
            new TransformShape(
                Translate(-roadW / 2 - 2.5f, 0, z),
                new Tree(5.0f)
            )
        );

        // Phải
        parts.push_back(
            new TransformShape(
                Translate(roadW / 2 + 2.5f, 0, z),
                new Tree(5.0f)
            )
        );
    }
}

RoadWithTrees::~RoadWithTrees() {
    for (auto p : parts)
        delete p;
}

void RoadWithTrees::draw(const mat4& modelMatrix) const {

    for (size_t i = 0; i < parts.size(); i++) {

        if (i == 0 || i == 1) {
            // Vỉa hè trái & phải
            Materials::Sidewalk.apply();
        }
        else if (i == 2) {
            // Mặt đường
            Materials::ConcreteDark.apply();
        }
        else {
            // Vạch kẻ + cây
            Materials::FloorTile.apply();   // trắng ngà / sáng
        }

        parts[i]->draw(modelMatrix);
    }
}

