#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include "Material.h"

#include "Angel.h"
typedef vec4 point4;
typedef vec4 color4;
class Shape {
public:
    virtual ~Shape() {}  // Destructor ảo để delete đúng
    virtual void draw(const mat4& modelMatrix) const = 0;  // Pure virtual: bắt buộc implement

protected:
    Material material;
    GLuint vao = 0;
    GLuint buffer = 0;
    int numPoints = 0;

    // Hàm chung để init buffer (các subclass override nếu cần)
    virtual void initGPUBuffers() = 0;
};

#endif