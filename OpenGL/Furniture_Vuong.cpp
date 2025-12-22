#include "Furniture_Vuong.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

// =========================================================
// 1. BÀN TRÀ (Chân gỗ, Mặt kính)
// =========================================================
CoffeeTable::CoffeeTable() {
    float w = 1.2f; float h = 0.5f; float d = 0.8f;
    float legW = 0.1f;
    float topT = 0.05f; // Độ dày mặt bàn

    // 4 Chân bàn (Gỗ)
    TransformShape* leg1 = new TransformShape(Translate(-w / 2 + legW / 2, h / 2, -d / 2 + legW / 2) * Scale(legW, h, legW), new Cube());
    TransformShape* leg2 = new TransformShape(Translate(w / 2 - legW / 2, h / 2, -d / 2 + legW / 2) * Scale(legW, h, legW), new Cube());
    TransformShape* leg3 = new TransformShape(Translate(-w / 2 + legW / 2, h / 2, d / 2 - legW / 2) * Scale(legW, h, legW), new Cube());
    TransformShape* leg4 = new TransformShape(Translate(w / 2 - legW / 2, h / 2, d / 2 - legW / 2) * Scale(legW, h, legW), new Cube());

    woodParts.push_back(leg1); woodParts.push_back(leg2);
    woodParts.push_back(leg3); woodParts.push_back(leg4);

    // Khung đỡ mặt bàn
    woodParts.push_back(new TransformShape(Translate(0, h - 0.1f, 0) * Scale(w, 0.05f, d), new Cube()));

    // Mặt bàn (Kính)
    glassParts.push_back(new TransformShape(Translate(0, h, 0) * Scale(w, topT, d), new Cube()));
}

CoffeeTable::~CoffeeTable() {
    for (auto p : woodParts) delete p;
    for (auto p : glassParts) delete p;
}

void CoffeeTable::draw(const mat4& model) const {
    // 1. VẼ CHÂN GỖ (Vật thể đặc - KHÔNG Blend)
    // Đảm bảo tắt Blend để gỗ đặc
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);

    Materials::Wood.apply();
    for (auto p : woodParts) p->draw(model);

    // 2. VẼ MẶT KÍNH (Vật thể trong - CÓ Blend)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE); // Tắt ghi độ sâu để nhìn xuyên qua kính

    Materials::Glass.apply(); // Kính cho mặt
    for (auto p : glassParts) p->draw(model);

    // 3. DỌN DẸP (Trả lại trạng thái gốc)
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

// =========================================================
// 2. SOFA (Hình chữ L hoặc dài)
// =========================================================
Sofa::Sofa() {
    float w = 2.5f; float seatH = 0.45f; float d = 0.9f;
    float backH = 0.9f; float backThick = 0.2f;
    float armW = 0.2f;

    // Đệm ngồi
    parts.push_back(new TransformShape(Translate(0, seatH / 2, 0) * Scale(w, seatH, d), new Cube()));

    // Tựa lưng
    parts.push_back(new TransformShape(Translate(0, backH / 2, -d / 2 + backThick / 2) * Scale(w, backH, backThick), new Cube()));

    // Tay vịn trái
    parts.push_back(new TransformShape(Translate(-w / 2 + armW / 2, (seatH + 0.2f) / 2, 0) * Scale(armW, seatH + 0.2f, d), new Cube()));

    // Tay vịn phải
    parts.push_back(new TransformShape(Translate(w / 2 - armW / 2, (seatH + 0.2f) / 2, 0) * Scale(armW, seatH + 0.2f, d), new Cube()));
}

Sofa::~Sofa() { for (auto p : parts) delete p; }

void Sofa::draw(const mat4& model) const {
    Materials::FabricGrey.apply(); // Hoặc FabricRed
    for (auto p : parts) p->draw(model);
}

// =========================================================
// 3. KỆ GỖ TRƯNG BÀY TÀU HỎA
// =========================================================
WoodShelf::WoodShelf() {
    float w = 3.0f; float h = 2.0f; float d = 0.4f;
    float thick = 0.05f; // Độ dày ván
    int numShelves = 4; // 4 tầng

    // 2 Tấm bên hông
    parts.push_back(new TransformShape(Translate(-w / 2 + thick / 2, h / 2, 0) * Scale(thick, h, d), new Cube()));
    parts.push_back(new TransformShape(Translate(w / 2 - thick / 2, h / 2, 0) * Scale(thick, h, d), new Cube()));

    // Tấm lưng (mỏng)
    parts.push_back(new TransformShape(Translate(0, h / 2, -d / 2 + thick / 2) * Scale(w, h, thick), new Cube()));

    // Các đợt ngang (Kệ)
    float gap = h / numShelves;
    for (int i = 0; i <= numShelves; i++) {
        float y = i * gap + thick / 2;
        if (i == 0) y = thick / 2; // Đáy sát đất
        parts.push_back(new TransformShape(Translate(0, y, 0) * Scale(w - 2 * thick, thick, d), new Cube()));
    }
}

WoodShelf::~WoodShelf() { for (auto p : parts) delete p; }

void WoodShelf::draw(const mat4& model) const {
    Materials::Wood.apply();
    for (auto p : parts) p->draw(model);
}

// =========================================================
// 4. TỦ KÍNH TRƯNG BÀY
// =========================================================
GlassCabinet::GlassCabinet() {
    float w = 1.0f; float h = 1.8f; float d = 0.5f;
    float thick = 0.05f;

    // --- KHUNG KIM LOẠI ---
    // 4 Cột đứng
    frameParts.push_back(new TransformShape(Translate(-w / 2, h / 2, -d / 2) * Scale(thick, h, thick), new Cube()));
    frameParts.push_back(new TransformShape(Translate(w / 2, h / 2, -d / 2) * Scale(thick, h, thick), new Cube()));
    frameParts.push_back(new TransformShape(Translate(-w / 2, h / 2, d / 2) * Scale(thick, h, thick), new Cube()));
    frameParts.push_back(new TransformShape(Translate(w / 2, h / 2, d / 2) * Scale(thick, h, thick), new Cube()));

    // Khung ngang (Đỉnh và Đáy)
    frameParts.push_back(new TransformShape(Translate(0, thick / 2, 0) * Scale(w, thick, d), new Cube())); // Đáy
    frameParts.push_back(new TransformShape(Translate(0, h - thick / 2, 0) * Scale(w, thick, d), new Cube())); // Đỉnh

    // --- KÍNH ---
    // Các mặt kính bao quanh (Trừ mặt trước để mở hoặc làm cửa)
    // Kính sau
    glassParts.push_back(new TransformShape(Translate(0, h / 2, -d / 2) * Scale(w - thick, h - thick, 0.01f), new Cube()));
    // Kính trái
    glassParts.push_back(new TransformShape(Translate(-w / 2, h / 2, 0) * Scale(0.01f, h - thick, d - thick), new Cube()));
    // Kính phải
    glassParts.push_back(new TransformShape(Translate(w / 2, h / 2, 0) * Scale(0.01f, h - thick, d - thick), new Cube()));
    // Các đợt kính nằm ngang bên trong
    glassParts.push_back(new TransformShape(Translate(0, h * 0.33, 0) * Scale(w - thick, 0.01f, d - thick), new Cube()));
    glassParts.push_back(new TransformShape(Translate(0, h * 0.66, 0) * Scale(w - thick, 0.01f, d - thick), new Cube()));
}

GlassCabinet::~GlassCabinet() {
    for (auto p : frameParts) delete p;
    for (auto p : glassParts) delete p;
}

// ================== DISPLAY TABLE ==================
DisplayTable::DisplayTable() {
    float w = 2.0f; float h = 0.8f; float d = 0.8f;
    float legW = 0.1f;

    // Mặt bàn dày
    parts.push_back(new TransformShape(Translate(0, h, 0) * Scale(w, 0.1f, d), new Cube()));

    // 4 Chân vững chắc
    parts.push_back(new TransformShape(Translate(-w / 2 + legW, h / 2, -d / 2 + legW) * Scale(legW, h, legW), new Cube()));
    parts.push_back(new TransformShape(Translate(w / 2 - legW, h / 2, -d / 2 + legW) * Scale(legW, h, legW), new Cube()));
    parts.push_back(new TransformShape(Translate(-w / 2 + legW, h / 2, d / 2 - legW) * Scale(legW, h, legW), new Cube()));
    parts.push_back(new TransformShape(Translate(w / 2 - legW, h / 2, d / 2 - legW) * Scale(legW, h, legW), new Cube()));
}

DisplayTable::~DisplayTable() { for (auto p : parts) delete p; }

void DisplayTable::draw(const mat4& model) const {
    Materials::ConcreteBeige.apply(); // Màu be sáng sủa
    for (auto p : parts) p->draw(model);
}

void GlassCabinet::draw(const mat4& model) const {
    // 1. VẼ KHUNG KIM LOẠI (Vật thể đặc)
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);

    Materials::Metal.apply();
    for (auto p : frameParts) p->draw(model);

    // 2. VẼ CÁC TẤM KÍNH (Vật thể trong)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    Materials::Glass.apply();
    for (auto p : glassParts) p->draw(model);

    // 3. DỌN DẸP
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}