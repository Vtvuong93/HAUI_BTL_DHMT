#include "Furniture_Vuong.h"
#include "TransformShape.h"
#include "MaterialLib.h"

#include "Cube.h"
#include "Cylinder.h"

using namespace Angel;

// ================== 1. BÀN TRÀ (Chân gỗ, Mặt kính) ==================
CoffeeTable::CoffeeTable() {
    float w = 1.2f; float h = 0.5f; float d = 0.8f;
    float legW = 0.1f, topT = 0.05f; 

    // 4 Chân bàn
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
    // 1. Vẽ phần gỗ (Đặc - Tắt Blend)
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    Materials::Wood.apply();
    for (auto p : woodParts) p->draw(model);

    // 2. Vẽ mặt kính (Trong suốt - Bật Blend)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE); // Tắt ghi độ sâu để nhìn xuyên qua kính
    Materials::Glass.apply(); 
    for (auto p : glassParts) p->draw(model);

    // 3. DỌN DẸP (Trả lại trạng thái gốc)
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

// ================== 2. SOFA (Chữ L hoặc Dài) ==================
Sofa::Sofa() {
    float w = 2.5f, seatH = 0.45f, d = 0.9f;
    float backH = 0.9f, backThick = 0.2f, armW = 0.2f;

    // Đệm ngồi & Tựa lưng
    parts.push_back(new TransformShape(Translate(0, seatH / 2, 0) * Scale(w, seatH, d), new Cube()));
    parts.push_back(new TransformShape(Translate(0, backH / 2, -d / 2 + backThick / 2) * Scale(w, backH, backThick), new Cube()));

	// Tay vịn trái & phải
    parts.push_back(new TransformShape(Translate(-w / 2 + armW / 2, (seatH + 0.2f) / 2, 0) * Scale(armW, seatH + 0.2f, d), new Cube()));
    parts.push_back(new TransformShape(Translate(w / 2 - armW / 2, (seatH + 0.2f) / 2, 0) * Scale(armW, seatH + 0.2f, d), new Cube()));
}

Sofa::~Sofa() { for (auto p : parts) delete p; }

void Sofa::draw(const mat4& model) const {
    Materials::FabricRed.apply();
    for (auto p : parts) p->draw(model);
}

// ================== 3. KỆ GỖ TRƯNG BÀY ==================
WoodShelf::WoodShelf() {
    float w = 4.0f, h = 3.5f, d = 0.75f, thick = 0.05f;
    int numShelves = 3;

    // 2 Tấm bên hông & Tấm lưng
    parts.push_back(new TransformShape(Translate(-w / 2 + thick / 2, h / 2, 0) * Scale(thick, h, d), new Cube()));
    parts.push_back(new TransformShape(Translate(w / 2 - thick / 2, h / 2, 0) * Scale(thick, h, d), new Cube()));
    parts.push_back(new TransformShape(Translate(0, h / 2, -d / 2 + thick / 2) * Scale(w, h, thick), new Cube()));

    // Các đợt ngang
    float gap = h / numShelves;
    for (int i = 0; i <= numShelves; i++) {
        float y = i * gap + thick / 2;
        if (i == 0) y = thick / 2; // Đáy sát đất
        parts.push_back(new TransformShape(Translate(0, y, 0) * Scale(w, thick, d), new Cube()));
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
    // Lưu vào biến thành viên để đồng bộ với hàm draw
    this->w = 3.5f; this->h = 2.5f; this->d = 1.0f;
    float thick = 0.05f;

    // --- 1. PHẦN TĨNH (KHUNG + KÍNH CỐ ĐỊNH) ---

    // 4 Cột đứng
    frameParts.push_back(new TransformShape(Translate(-w / 2, h / 2, -d / 2) * Scale(thick, h, thick), new Cube()));
    frameParts.push_back(new TransformShape(Translate(w / 2, h / 2, -d / 2) * Scale(thick, h, thick), new Cube()));
    frameParts.push_back(new TransformShape(Translate(-w / 2, h / 2, d / 2) * Scale(thick, h, thick), new Cube()));
    frameParts.push_back(new TransformShape(Translate(w / 2, h / 2, d / 2) * Scale(thick, h, thick), new Cube()));

    // Khung ngang (Đỉnh và Đáy)
    frameParts.push_back(new TransformShape(Translate(0, thick / 2, 0) * Scale(w, thick, d), new Cube()));
    frameParts.push_back(new TransformShape(Translate(0, h - thick / 2, 0) * Scale(w, thick, d), new Cube()));

    // Kính tĩnh (Sau, Trái, Phải, Đợt ngang)
    staticGlassParts.push_back(new TransformShape(Translate(0, h / 2, -d / 2) * Scale(w - thick, h - thick, 0.01f), new Cube()));
    staticGlassParts.push_back(new TransformShape(Translate(-w / 2, h / 2, 0) * Scale(0.01f, h - thick, d - thick), new Cube()));
    staticGlassParts.push_back(new TransformShape(Translate(w / 2, h / 2, 0) * Scale(0.01f, h - thick, d - thick), new Cube()));
    staticGlassParts.push_back(new TransformShape(Translate(0, h * 0.33, 0) * Scale(w - thick, 0.01f, d - thick), new Cube()));
    staticGlassParts.push_back(new TransformShape(Translate(0, h * 0.66, 0) * Scale(w - thick, 0.01f, d - thick), new Cube()));

    // 2. CỬA TRÁI & PHẢI (Dùng Struct)
    // Tay nắm
    leftDoor.handle.push_back(new TransformShape(Translate(-w / 8, h / 2, d / 2 + 0.01f) * Scale(0.05f, 0.2f, 0.02f), new Cube()));
    rightDoor.handle.push_back(new TransformShape(Translate(w / 8, h / 2, d / 2 + 0.01f) * Scale(0.05f, 0.2f, 0.02f), new Cube()));
    // Kính cửa
    leftDoor.glass.push_back(new TransformShape(Translate(-w / 4.1, h / 2, d / 2) * Scale((w - thick) / 2, h - thick, 0.01f), new Cube()));
    rightDoor.glass.push_back(new TransformShape(Translate(w / 4.1, h / 2, d / 2) * Scale((w - thick) / 2, h - thick, 0.01f), new Cube()));
}

GlassCabinet::~GlassCabinet() {
    for (auto p : frameParts) delete p;
    for (auto p : staticGlassParts) delete p;
    for (auto p : leftDoor.handle) delete p;
    for (auto p : leftDoor.glass) delete p;
    for (auto p : rightDoor.handle) delete p;
    for (auto p : rightDoor.glass) delete p;
}

// HÀM DRAW MỚI CÓ LOGIC XOAY CỬA
void GlassCabinet::draw(const mat4& model) const {
    // Tự động xoay dựa trên biến currentVal (kế thừa từ AnimatedShape)
    float angleDeg = this->currentVal * 90.0f; // 0 -> 90 độ

    // Ma trận xoay quanh bản lề
    mat4 mLeft = model * Translate(-w / 2, 0, d / 2) * RotateY(-angleDeg) * Translate(w / 2, 0, -d / 2);
    mat4 mRight = model * Translate(w / 2, 0, d / 2) * RotateY(angleDeg) * Translate(-w / 2, 0, -d / 2);

    // 1. VẼ PHẦN ĐẶC
    glDisable(GL_BLEND); glDepthMask(GL_TRUE);
    Materials::Metal.apply();
    for (auto p : frameParts) p->draw(model);
    for (auto p : leftDoor.handle) p->draw(mLeft);
    for (auto p : rightDoor.handle) p->draw(mRight);

    // 2. VẼ KÍNH
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glDepthMask(GL_FALSE);
    Materials::Glass.apply();
    for (auto p : staticGlassParts) p->draw(model);
    for (auto p : leftDoor.glass) p->draw(mLeft);
    for (auto p : rightDoor.glass) p->draw(mRight);

    glDepthMask(GL_TRUE); glDisable(GL_BLEND);
}

// ================== 5. BÀN TRƯNG BÀY (DisplayTable) ==================
DisplayTable::DisplayTable() {
    float w = 2.0f, h = 0.8f, d = 0.8f, legW = 0.1f;

    // Mặt bàn
    parts.push_back(new TransformShape(Translate(0, h, 0) * Scale(w, 0.1f, d), new Cube()));

    // 4 Chân
    parts.push_back(new TransformShape(Translate(-w / 2 + legW, h / 2, -d / 2 + legW) * Scale(legW, h, legW), new Cube()));
    parts.push_back(new TransformShape(Translate(w / 2 - legW, h / 2, -d / 2 + legW) * Scale(legW, h, legW), new Cube()));
    parts.push_back(new TransformShape(Translate(-w / 2 + legW, h / 2, d / 2 - legW) * Scale(legW, h, legW), new Cube()));
    parts.push_back(new TransformShape(Translate(w / 2 - legW, h / 2, d / 2 - legW) * Scale(legW, h, legW), new Cube()));
}

DisplayTable::~DisplayTable() { for (auto p : parts) delete p; }

void DisplayTable::draw(const mat4& model) const {
    Materials::ConcreteBeige.apply();
    for (auto p : parts) p->draw(model);
}

// ================== 6. BÀN TRÒN (ROUND TABLE) ==================
RoundTable::RoundTable() {
    float radius = 5.0f;   // Bán kính mặt bàn (Đường kính 1.2m)
    float height = 1.2f;  // Chiều cao bàn
    float thick = 0.1f;   // Độ dày mặt bàn
    float legR = 2.5f;    // Bán kính chân trụ

    // 1. Mặt bàn 
    parts.push_back(new TransformShape(Translate(0, height, 0) * Scale(radius, thick, radius), new Cylinder()));

    // 2. Chân trụ giữa 
    parts.push_back(new TransformShape(Translate(0, height / 2, 0) * Scale(legR, height, legR),new Cylinder()));

    // 3. Đế chân bàn 
    parts.push_back(new TransformShape(Translate(0, 0.05f, 0) * Scale(radius * 0.6f, thick, radius * 0.6f), new Cylinder()));
}

RoundTable::~RoundTable() { for (auto p : parts) delete p; }

void RoundTable::draw(const mat4& model) const {
    Materials::ConcreteBeige.apply();
    for (auto p : parts) p->draw(model);
}

// ================== SLIDING DOOR (CỬA TRƯỢT) ==================
SlidingGlassDoor::SlidingGlassDoor() {
    float w = 4.0f;   // Tổng chiều rộng cửa
    float h = 4.5f;   // Chiều cao
    float d = 0.145f;   // Độ dày khung bao
    float frameThick = 0.1f; // Độ dày thanh nhôm
    float glassThick = 0.02f;

    // --- 1. KHUNG  ---
    // Thanh ngang trên (Ray trượt)
    fixedFrame.push_back(new TransformShape(Translate(0, h - frameThick / 2, 0) * Scale(w, frameThick, d), new Cube()));
    // Thanh ngang dưới (Sàn)
    fixedFrame.push_back(new TransformShape(Translate(0, frameThick / 2, 0) * Scale(w, frameThick, d), new Cube()));

    // Helper Lambda để tạo cánh cửa (Tránh lặp code 2 lần)
    auto createLeaf = [&](float xCenter, DoorLeaf& leaf) {
        float doorW = w / 2 - 0.02f;
        float doorH = h - 2 * frameThick;
        // Khung trên/dưới
        leaf.frame.push_back(new TransformShape(Translate(xCenter, h / 2 + doorH / 2 - 0.05f, 0) * Scale(doorW + 0.015, 0.1f, 0.05f), new Cube()));
        leaf.frame.push_back(new TransformShape(Translate(xCenter, h / 2 - doorH / 2 + 0.05f, 0) * Scale(doorW + 0.015, 0.1f, 0.05f), new Cube()));
        // Khung trái/phải
        leaf.frame.push_back(new TransformShape(Translate(xCenter - doorW / 2 + 0.05f, h / 2, 0) * Scale(0.115f, doorH, 0.05f), new Cube()));
        leaf.frame.push_back(new TransformShape(Translate(xCenter + doorW / 2 - 0.05f, h / 2, 0) * Scale(0.115f, doorH, 0.05f), new Cube()));
        // Tay nắm (dịch sang bên một chút tùy cánh)
        float handleOffset = (xCenter < 0) ? 0.65f : -0.65f;
        leaf.handle.push_back(new TransformShape(Translate(xCenter + handleOffset, h / 2, 0.05f) * Scale(0.05f, 0.4f, 0.02f), new Cube()));
        // Kính
        leaf.glass.push_back(new TransformShape(Translate(xCenter, h / 2, 0) * Scale(doorW - 0.2f, doorH - 0.2f, glassThick), new Cube()));
        };

	// Tạo cánh trái & phải
    createLeaf(-w / 4, leftLeaf);
	createLeaf(w / 4, rightLeaf);
}

SlidingGlassDoor::~SlidingGlassDoor() {
    for (auto p : fixedFrame) delete p;
    // Xóa bộ nhớ trong struct
    auto deleteLeaf = [](DoorLeaf& leaf) {
        for (auto p : leaf.frame) delete p;
        for (auto p : leaf.glass) delete p;
        for (auto p : leaf.handle) delete p;
    };
    deleteLeaf(leftLeaf);
    deleteLeaf(rightLeaf);
}

void SlidingGlassDoor::draw(const mat4& model) const {
    float slideDist = this->currentVal * 1.8f; // Dùng currentVal của AnimatedShape

    mat4 mLeft = model * Translate(-slideDist, 0, 0);
    mat4 mRight = model * Translate(slideDist, 0, 0);

    // 1. PHẦN ĐẶC
    glDisable(GL_BLEND); glDepthMask(GL_TRUE);
    Materials::Metal.apply();
    for (auto p : fixedFrame) p->draw(model);

    for (auto p : leftLeaf.frame) p->draw(mLeft);
    for (auto p : leftLeaf.handle) p->draw(mLeft);

    for (auto p : rightLeaf.frame) p->draw(mRight);
    for (auto p : rightLeaf.handle) p->draw(mRight);

    // 2. KÍNH
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glDepthMask(GL_FALSE);
    Materials::Glass.apply();
    for (auto p : leftLeaf.glass) p->draw(mLeft);
    for (auto p : rightLeaf.glass) p->draw(mRight);

    glDepthMask(GL_TRUE); glDisable(GL_BLEND);
}
