#include "BalconyRailing.h"
#include "MaterialLib.h"

using namespace Angel;

BalconyRailing::BalconyRailing() {
    topBar = new Cube();
    bottomBar = new Cube();
    pillar = new Cube();
}

BalconyRailing::~BalconyRailing() {
    delete topBar;
    delete bottomBar;
    delete pillar;
}

void BalconyRailing::draw(const mat4& modelMatrix) const {

    // ================== THÔNG SỐ ==================
    float width = 10.0f;     // ngang ban công
    float height = 1.2f;     // cao hàng rào
    float thickness = 0.15f;
    float depth = 0.15f;
    float sideDepth = 3.0f; // chiều sâu ban công (2 bên)

    int pillarCount = 9;
    float spacing = width / (pillarCount - 1);

    Materials::Metal.apply();

    // ==================================================
    // =============== HÀNG RÀO PHÍA TRƯỚC ===============
    // ==================================================

    // Thanh trên
    topBar->draw(
        modelMatrix *
        Translate(0.0f, height, 0.0f) *
        Scale(width, thickness, depth)
    );

    // Thanh dưới
    bottomBar->draw(
        modelMatrix *
        Translate(0.0f, thickness / 2, 0.0f) *
        Scale(width, thickness, depth)
    );

    // Cột đứng
    for (int i = 0; i < pillarCount; i++) {
        float x = -width / 2 + i * spacing;

        pillar->draw(
            modelMatrix *
            Translate(x, height / 2, 0.0f) *
            Scale(thickness, height, depth)
        );
    }

    // ==================================================
    // =============== HÀNG RÀO BÊN TRÁI =================
    // ==================================================

    topBar->draw(
        modelMatrix *
        Translate(-width / 2 + thickness / 2,
            height,
            sideDepth / 2 - 3.0f) *
        Scale(thickness, thickness, sideDepth)
    );

    bottomBar->draw(
        modelMatrix *
        Translate(-width / 2 + thickness / 2,
            thickness / 2,
            sideDepth / 2 - 3.0f) *
        Scale(thickness, thickness, sideDepth)
    );

    pillar->draw(
        modelMatrix *
        Translate(-width / 2 + thickness / 2,
            height / 2,
            sideDepth / 2 - 3.0f) *
        Scale(thickness, height, thickness)
    );

    // ==================================================
    // =============== HÀNG RÀO BÊN PHẢI =================
    // ==================================================

    topBar->draw(
        modelMatrix *
        Translate(width / 2 - thickness / 2,
            height,
            sideDepth / 2 - 3.0f) *
        Scale(thickness, thickness, sideDepth)
    );

    bottomBar->draw(
        modelMatrix *
        Translate(width / 2 - thickness / 2,
            thickness / 2,
            sideDepth / 2 - 3.0f) *
        Scale(thickness, thickness, sideDepth)
    );

    pillar->draw(
        modelMatrix *
        Translate(width / 2 - thickness / 2,
            height / 2,
            sideDepth / 2 - 3.0f) *
        Scale(thickness, height, thickness)
    );
}
