#pragma once

#include "Angel.h"
#include <vector>
#include "TransformShape.h"

#include "Cube.h" 
#include "Cylinder.h"

// Class hỗ trợ Animation tự động
class AnimatedShape : public Shape {
public:
    float currentVal = 0.0f; // Giá trị hiện tại (0.0 -> 1.0)
    float targetVal = 0.0f;  // Giá trị đích
    float speed = 0.05f;     // Tốc độ chuyển động

    void update() {
        if (abs(currentVal - targetVal) > 0.001f) {
            float step = (targetVal - currentVal) * 0.05f; // Hiệu ứng Ease-out (gần đích thì chậm lại)
            if (abs(step) < 0.001f) step = (targetVal > currentVal) ? 0.001f : -0.001f; // Đảm bảo không đứng im
            currentVal += step;
        }
        else {
            currentVal = targetVal;
        }
    }
    void toggle() { targetVal = (targetVal == 0.0f) ? 1.0f : 0.0f; }
};

// 1. Bàn trà (Gỗ & Kính)
class CoffeeTable : public Shape {
public:
    CoffeeTable();
    ~CoffeeTable();
    void draw(const mat4& modelMatrix) const override;
private:
    std::vector<Shape*> woodParts;  // Phần gỗ
    std::vector<Shape*> glassParts; // Phần kính
    void initGPUBuffers() override {}
};

// 2. Ghế Sofa
class Sofa : public Shape {
public:
    Sofa();
    ~Sofa();
    void draw(const mat4& modelMatrix) const override;
private:
    std::vector<Shape*> parts;
    void initGPUBuffers() override {}
};

// 3. Kệ gỗ trưng bày
class WoodShelf : public Shape {
public:
    WoodShelf();
    ~WoodShelf();
    void draw(const mat4& modelMatrix) const override;
private:
    std::vector<Shape*> parts;
    void initGPUBuffers() override {}
};

// 4. Tủ kính trưng bày
class GlassCabinet : public AnimatedShape {
public:
    GlassCabinet();
    ~GlassCabinet();
    void draw(const mat4& modelMatrix) const override;

private:
    float w, h, d; 
    std::vector<Shape*> frameParts;       // Khung tĩnh
    std::vector<Shape*> staticGlassParts; // Kính tĩnh (lưng, hông)

    // Gom nhóm cửa để quản lý
    struct Door {
        std::vector<Shape*> handle;
        std::vector<Shape*> glass;
    } leftDoor, rightDoor;

    void initGPUBuffers() override {}
};

// 5. Bàn trưng bày dài
class DisplayTable : public Shape {
public:
    DisplayTable();
    ~DisplayTable();
    void draw(const mat4& modelMatrix) const override;
private:
    std::vector<Shape*> parts;
    void initGPUBuffers() override {}
};

// 6. Bàn tròn
class RoundTable : public Shape {
public:
	RoundTable();
    ~RoundTable();
    void draw(const mat4& modelMatrix, float openAngle) const;
    void draw(const mat4& modelMatrix) const override;
private:
    std::vector<Shape*> parts;
    void initGPUBuffers() override {}
};

// 7. Cửa kính trượt
class SlidingGlassDoor : public AnimatedShape {
public:
    SlidingGlassDoor();
    ~SlidingGlassDoor();
    void draw(const mat4& modelMatrix) const override;
private:
    // Khung bao ngoài (Cố định)
    std::vector<Shape*> fixedFrame;

    // Struct phân cấp rõ ràng: Cánh cửa gồm Khung, Kính, Tay nắm
    struct DoorLeaf {
        std::vector<Shape*> frame;
        std::vector<Shape*> glass;
        std::vector<Shape*> handle;
    } leftLeaf, rightLeaf;

    void initGPUBuffers() override {}
};
