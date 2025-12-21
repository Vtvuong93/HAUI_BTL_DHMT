#include "DenChieuSang.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

DenChieuSang::DenChieuSang() {
    // 1. ?? ?èn g?n vào tr?n (Hình tr? d?t)
    parts.push_back(new TransformShape(
        Scale(0.4f, 0.05f, 0.4f),
        new Cylinder()
    ));

     //2. Thân ?èn r?i (Hình tr? dài h?n)
    parts.push_back(new TransformShape(
        Translate(0.0f, -0.1f, 0.0f) * Scale(0.2f, 0.1f, 0.2f),
        new Cylinder()
    ));

    // 3. Bóng ?èn (Kh?i nh? n?m bên trong thân ?èn)
    parts.push_back(new TransformShape(
        Translate(0.0f, 0.02f, 0.0f) * Scale(0.15f, 0.05f, 0.15f),
        new Cylinder()
    ));
}

DenChieuSang::~DenChieuSang() {
    for (auto p : parts) delete p;
}

void DenChieuSang::draw(const mat4& modelMatrix) const {
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i == 0 || i == 1) {
            Materials::Metal.apply(); // Thân ?èn màu kim lo?i
        }
        else {
            // Ph?n bóng ?èn: S? d?ng v?t li?u sáng nh?t 
            Materials::Ceiling.apply();
            
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        parts[i]->draw(modelMatrix);
    }
}