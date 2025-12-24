// Globals.cpp
#include "Globals.h"

// Định nghĩa thực tế các biến toàn cục (definition)
// Đây là nơi cấp phát bộ nhớ cho chúng
GLuint program;
GLuint model_loc = 0;
GLuint view_loc = 0;
GLuint projection_loc = 0;

float rolledDoor = 1.0f;
float drag = 0;

bool g_trainMove = false;   // mặc định: đứng yên
bool g_TrainMove1 = false;  // di chuyển phần đầu
bool g_TrainMove2 = false;  // di chuyển phần sau

float twistKey = 0.0f;