#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include "Angel.h"

// Biến toàn cục cho shader program
extern GLuint program;          // ID của shader program (tạo bởi InitShader)

// Các uniform location – được lấy một lần trong shaderSetup() và dùng lại khắp nơi
extern GLuint model_loc;        // location của uniform mat4 Model
extern GLuint view_loc;         // location của uniform mat4 View
extern GLuint projection_loc;   // location của uniform mat4 Projection


extern float rolledDoor;
extern float drag;

extern bool g_trainMove;

// Nếu sau này bạn muốn thêm các uniform khác (ví dụ: NormalMatrix, Material, ...)
// thì khai báo extern ở đây luôn để dễ quản lý

#endif // GLOBALS_H