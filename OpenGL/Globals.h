#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

// ================== THƯ VIỆN CHUẨN ==================
#include "Windows.h"
#include <cstdlib>
#include <algorithm> 

// ================== THƯ VIỆN ĐỒ HỌA & PROJECT ==================
#include "Angel.h"
#include "TransformShape.h"
#include "Scene.h"
#include "camera.h"

// ================== THƯ VIỆN OBJECTS ==================
#include "house.h"
#include "HouseModern.h"
#include "HouseModern3F.h"
#include "Road.h"

#include "ToyTrain.h"
#include "ToyTrain1.h"
#include "CycleRail.h"
#include "CityInside.h"
#include "StraightRail.h"
#include "ToyLocomotive2.h"
#include "ToyLocomotive3.h"
#include "ToyLocomotive4.h"

#include "BienHieu.h"
#include "PosterQuangCao.h"
#include "DenChieuSang.h"

#include "Furniture_Vuong.h"
#include "Toys_Vuong.h"
#include "Lights.h"

// ================== BIẾN TOÀN CỤC ==================
extern GLuint program;          // ID của shader program (tạo bởi InitShader)

// Các uniform location – được lấy một lần trong shaderSetup() và dùng lại khắp nơi
extern GLuint model_loc;        // location của uniform mat4 Model
extern GLuint view_loc;         // location của uniform mat4 View
extern GLuint projection_loc;   // location của uniform mat4 Projection

extern bool g_trainMove; // trạng thái di chuyển của tàu
extern float rolledDoor;
extern float drag;
extern float twistKey;

#endif 