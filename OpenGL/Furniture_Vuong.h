#pragma once
#ifndef FURNITURE_H
#define FURNITURE_H

#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h" // Nếu bạn có cylinder làm chân bàn
#include <vector>

// 1. Bàn trà phòng khách
class CoffeeTable : public Shape {
public:
    CoffeeTable();
    ~CoffeeTable();
    void draw(const mat4& modelMatrix) const override;
private:
    std::vector<Shape*> woodParts; // Phần gỗ
    std::vector<Shape*> glassParts; // Phần kính (mặt bàn)
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

// 3. Kệ gỗ trưng bày tàu hỏa (Nhiều tầng)
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
    void draw(const mat4& modelMatrix) const override;
private:
    std::vector<Shape*> frameParts; // Khung
    std::vector<Shape*> glassParts; // Kính
    void initGPUBuffers() override {}
};

// 5. Bàn trưng bày dài (Museum Table)
class DisplayTable : public Shape {
public:
    DisplayTable();
    ~DisplayTable();
    void draw(const mat4& modelMatrix) const override;
private:
    std::vector<Shape*> parts;
    void initGPUBuffers() override {}
};

#endif