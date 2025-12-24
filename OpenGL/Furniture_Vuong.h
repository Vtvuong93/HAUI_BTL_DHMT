#pragma once
#ifndef FURNITURE_H
#define FURNITURE_H

#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"
#include <vector>

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
class GlassCabinet : public Shape {
public:
    GlassCabinet();
    ~GlassCabinet();
    float openAngle = 0.0f; // Góc mở cửa
    void draw(const mat4& modelMatrix) const override;

private:
    std::vector<Shape*> frameParts;       // Khung tĩnh
    std::vector<Shape*> staticGlassParts; // Kính tĩnh (lưng, hông)

    // CỬA TRÁI
    std::vector<Shape*> leftDoorGlass;    // Phần kính cửa trái
    std::vector<Shape*> leftDoorHandle;   // Phần tay nắm cửa trái

    // CỬA PHẢI
    std::vector<Shape*> rightDoorGlass;   // Phần kính cửa phải
    std::vector<Shape*> rightDoorHandle;  // Phần tay nắm cửa phải

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
class SlidingGlassDoor : public Shape {
public:
    SlidingGlassDoor();
    ~SlidingGlassDoor();
    float openFactor = 0.0f;
    void draw(const mat4& modelMatrix) const override;
private:
    // Khung bao ngoài (Cố định)
    std::vector<Shape*> fixedFrame;

    // Cánh trái (Khung + Tay nắm + Kính)
    std::vector<Shape*> leftDoorFrame;   // Phần đặc
    std::vector<Shape*> leftDoorGlass;   // Phần kính

    // Cánh phải (Khung + Tay nắm + Kính)
    std::vector<Shape*> rightDoorFrame;  // Phần đặc
    std::vector<Shape*> rightDoorGlass;  // Phần kính

    void initGPUBuffers() override {}
};

// 8. Tranh treo tường (Khung gỗ + Tranh)
class WallPicture : public Shape {
public:
    WallPicture(float w, float h); // Cho phép tùy chỉnh kích thước
    ~WallPicture();
    void draw(const mat4& modelMatrix) const override;

private:
    float width, height;
    std::vector<Shape*> frameParts; // Khung tranh
    std::vector<Shape*> canvasParts; // Phần tranh (nơi dán ảnh)

    void initGPUBuffers() override {}
};
#endif