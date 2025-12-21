#include "HouseModern.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include "BalconyRailing.h"
#include "Stair.h"

using namespace Angel;

HouseModern::HouseModern() {

    float wallT = 0.15f;
    float width = 12.0f;
    float depth = 18.0f;
    float floorH = 6.0f;
    float totalH = floorH * 2;

    float doorW = 4.0f;
    float doorH = floorH * 0.75f;

    float balconyD = 3.0f;
    float stairW = 4.0f;
    float stairD = 7.0f;

    // ==================================================
    // ================== SÀN TẦNG 1 ====================
    // ==================================================
    parts.push_back(
        new TransformShape(
            Translate(0, 0, 0) *
            Scale(width, wallT, depth),
            new Cube()
        )
    );

    // ==================================================
    // ================= TRẦN TẦNG 1 ====================
    // (Chừa lỗ cầu thang giữa nhà)
    // ==================================================

    // Bên trái lỗ thang
    parts.push_back(
        new TransformShape(
            Translate(-(stairW + 1.0f) / 2,
                floorH,
                0) *
            Scale((width - stairW) / 2,
                wallT,
                depth),
            new Cube()
        )
    );

    // Bên phải lỗ thang
    parts.push_back(
        new TransformShape(
            Translate((stairW + 1.0f) / 2,
                floorH,
                0) *
            Scale((width - stairW) / 2,
                wallT,
                depth),
            new Cube()
        )
    );

    // ==================================================
    // ================== BAN CÔNG ======================
    // ==================================================
    parts.push_back(
        new TransformShape(
            Translate(0,
                floorH,
                depth / 2 + balconyD / 2) *
            Scale(width,
                wallT,
                balconyD),
            new Cube()
        )
    );

    parts.push_back(
        new TransformShape(
            Translate(0,
                floorH + 0.01f,
                depth / 2 + balconyD - 0.075f),
            new BalconyRailing()
        )
    );

    // ==================================================
    // ================= TRẦN TẦNG 2 ====================
    // ==================================================
    parts.push_back(
        new TransformShape(
            Translate(0, totalH, 0) *
            Scale(width, wallT, depth),
            new Cube()
        )
    );

    // ==================================================
    // ==================== TƯỜNG =======================
    // ==================================================

    // Tường sau
    parts.push_back(
        new TransformShape(
            Translate(0, totalH / 2, -depth / 2) *
            Scale(width, totalH, wallT),
            new Cube()
        )
    );

    // Tường trái
    parts.push_back(
        new TransformShape(
            Translate(-width / 2, totalH / 2, 0) *
            Scale(wallT, totalH, depth),
            new Cube()
        )
    );

    // Tường phải
    parts.push_back(
        new TransformShape(
            Translate(width / 2, totalH / 2, 0) *
            Scale(wallT, totalH, depth),
            new Cube()
        )
    );

    // ==================================================
    // ============ MẶT TRƯỚC – TẦNG 1 ==================
    // ==================================================

    // Tường trái cửa
    parts.push_back(
        new TransformShape(
            Translate(-(doorW + (width - doorW) / 2) / 2,
                floorH / 2,
                depth / 2) *
            Scale((width - doorW) / 2,
                floorH,
                wallT),
            new Cube()
        )
    );

    // Tường phải cửa
    parts.push_back(
        new TransformShape(
            Translate((doorW + (width - doorW) / 2) / 2,
                floorH / 2,
                depth / 2) *
            Scale((width - doorW) / 2,
                floorH,
                wallT),
            new Cube()
        )
    );

    // Phần tường trên cửa
    parts.push_back(
        new TransformShape(
            Translate(0,
                doorH + (floorH - doorH) / 2,
                depth / 2) *
            Scale(doorW,
                floorH - doorH,
                wallT),
            new Cube()
        )
    );

    // ==================================================
    // =================== CẦU THANG ====================
    // ==================================================
    parts.push_back(
        new TransformShape(
            Translate(0,
                0,
                -depth / 2 + stairD / 2 + 1.0f +5.0f),
            new Stair(floorH)
        )
    );

    // ==================================================
    // ============ MẶT TRƯỚC – TẦNG 2 ==================
    // ==================================================
    parts.push_back(
        new TransformShape(
            Translate(0,
                floorH + floorH / 2,
                depth / 2) *
            Scale(width,
                floorH,
                wallT),
            new Cube()
        )
    );
}

HouseModern::~HouseModern() {
    for (auto p : parts)
        delete p;
}

void HouseModern::draw(const mat4& modelMatrix) const {
    for (auto p : parts) {
        Materials::ConcreteBlue.apply();
        p->draw(modelMatrix);
    }
}
