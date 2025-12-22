#include "House.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include "BalconyRailing.h"
#include "Stair.h"
#include "Door.h"
#include "CashierCounter.h"

using namespace Angel;

House::House() {
    float wallT = 0.15f;
    float width = 10.0f;
    float depth = 20.0f;
    float floorH = 6.0f;
    float totalH = floorH * 2;

    float doorW = 4.0f;
    float doorH = floorH * 0.75f;

    // ===== BAN CÔNG & CẦU THANG =====
    float balconyD = 3.0f;
    float stairW = 5.0f;
    float stairD1 = 3.0f;
    float stairD2 = 5.0f;
    float stairD = stairD1 + stairD2;

    // ==================================================
    // =================== SÀN TẦNG 1 ===================
    // ==================================================
    parts.push_back(
        new TransformShape(
            Translate(0.0f, 0.0f, 0.0f) *
            Scale(width, wallT, depth),
            new Cube()
        )
    );

    float yCeil1 = floorH;

    // ==================================================
    // =============== TRẦN TẦNG 1 ======================
    // ==================================================

    // --------- TRẦN CHÍNH (BÊN TRÁI) ----------
    parts.push_back(
        new TransformShape(
            Translate(-(stairW) / 2 -0.45f,
                yCeil1,
                -width + 2.5f/2) *
            Scale(width - stairW -2*0.45f,
                wallT,
                2.5f),
            new Cube()
        )
    );

    // --------- TRẦN CHÍNH (BÊN PHẢI – PHÍA TRƯỚC) ----------
    parts.push_back(
        new TransformShape(
            Translate(0.0f ,
                yCeil1,
                (depth - stairD + balconyD)/2 - 2.0f - 8.0f/2) *
            Scale(width,
                wallT,
                depth - stairD - balconyD + 9.0f),
            new Cube()
        )
    );

    parts.push_back(
        new TransformShape(
            Translate(0.0f,
                floorH + 0.01f,                 // trên trần tầng 1
                depth / 2 + balconyD - 0.075f   // mép ngoài ban công
            ),
            new BalconyRailing()
        )
    );

    // quay thu ngan
    float table_h = 1.2f;
    parts.push_back(
        new TransformShape(
            Translate(-2.6f, table_h / 2, 7.8f) * RotateY(90),
            new CashierCounter(4.0f, table_h, 1.2f)
        )
    );

    // (GÓC PHẢI PHÍA SAU → LỖ CẦU THANG, KHÔNG TẠO)

    // --------- BAN CÔNG PHÍA TRƯỚC ----------
    parts.push_back(
        new TransformShape(
            Translate(0.0f,
                yCeil1,
                depth / 2 + balconyD / 2) *
            Scale(width,
                wallT,
                balconyD),
            new Cube()
        )
    );

    // ==================================================
    // =================== TRẦN TẦNG 2 ==================
    // ==================================================
    parts.push_back(
        new TransformShape(
            Translate(0.0f, totalH, 0.0f) *
            Scale(width, wallT, depth),
            new Cube()
        )
    );

    // ==================================================
    // ======================= TƯỜNG ===================
    // ==================================================

    // Tường sau
    parts.push_back(
        new TransformShape(
            Translate(0.0f, totalH / 2, -depth / 2) *
            Scale(width, totalH, wallT),
            new Cube()
        )
    );

    // Tường trái
    parts.push_back(
        new TransformShape(
            Translate(-width / 2, totalH / 2, 0.0f) *
            Scale(wallT, totalH, depth),
            new Cube()
        )
    );

    // Tường phải
    parts.push_back(
        new TransformShape(
            Translate(width / 2, totalH / 2, 0.0f) *
            Scale(wallT, totalH, depth),
            new Cube()
        )
    );

    // ==================================================
    // ============ TƯỜNG TRƯỚC – TẦNG 1 ================
    // ==================================================
    parts.push_back(
        new TransformShape(
            Translate(-(doorW + (width - doorW) / 2) / 2,
                floorH / 2,
                depth / 2) *
            Scale((width - doorW) / 2, floorH, wallT),
            new Cube()
        )
    );

    parts.push_back(
        new TransformShape(
            Translate((doorW + (width - doorW) / 2) / 2,
                floorH / 2,
                depth / 2) *
            Scale((width - doorW) / 2, floorH, wallT),
            new Cube()
        )
    );

    parts.push_back(
        new TransformShape(
            Translate(0.0f,
                doorH + (floorH - doorH) / 2,
                depth / 2) *
            Scale(doorW, floorH - doorH, wallT),
            new Cube()
        )
    );
    parts.push_back(
        new TransformShape(
            Translate(
                0.0f,
                doorH / 2,
                depth / 2),
            new Door(doorW, doorH, vec3(0, doorH / 2, 0.5)) // 
        )
    );

    // stair 
    parts.push_back(
        new TransformShape(
            Translate(
                width / 2 - stairW / 2,   // sát tường phải
                0.0f,                     // từ sàn tầng 1
                -depth / 2 + stairD / 2 + 2.5f  // sát tường sau
            ),
            new Stair(floorH)
        )
    );

    // ==================================================
    // ============ TƯỜNG TRƯỚC – TẦNG 2 ================
    // ==================================================
    parts.push_back(
        new TransformShape(
            Translate(-(doorW + (width - doorW) / 2) / 2,
                floorH + floorH / 2,
                depth / 2) *
            Scale((width - doorW) / 2, floorH, wallT),
            new Cube()
        )
    );

    parts.push_back(
        new TransformShape(
            Translate((doorW + (width - doorW) / 2) / 2,
                floorH + floorH / 2,
                depth / 2) *
            Scale((width - doorW) / 2, floorH, wallT),
            new Cube()
        )
    );

    parts.push_back(
        new TransformShape(
            Translate(0.0f,
                floorH + doorH + (floorH - doorH) / 2,
                depth / 2) *
            Scale(doorW, floorH - doorH, wallT),
            new Cube()
        )
    );
    
}

House::~House() {
    for (auto p : parts)
        delete p;
}

void House::draw(const mat4& modelMatrix) const {
    for (auto p : parts) {
        Materials::ConcreteSage.apply();
        p->draw(modelMatrix);
    }
}
