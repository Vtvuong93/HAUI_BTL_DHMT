#include "PosterQuangCao.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

PosterQuangCao::PosterQuangCao() {
    float w = 2.0f;  // Chi?u r?ng poster
    float h = 2.5f;  // Chi?u cao poster
    float t = 0.1f;  // ?? dày t?m b?ng
    float zF = t / 2 + 0.01f; // M?t ph?ng v? h?a ti?t (??y lên m?t chút)

    // 1. T?m n?n Poster (Màu tr?ng sáng)
    parts.push_back(new TransformShape(Scale(w, h, t), new Cube()));

    // --- H?A TI?T TÀU H?A ---
    // 2. Thân tàu (Kh?i ngang màu xanh d??ng)
    parts.push_back(new TransformShape(Translate(-0.2f, -0.4f, zF) * Scale(1.0f, 0.5f, 0.05f), new Cube()));

    // 3. Bu?ng lái (Kh?i ??ng màu ??)
    parts.push_back(new TransformShape(Translate(0.4f, -0.15f, zF) * Scale(0.5f, 1.0f, 0.05f), new Cube()));

    // 4. Mái bu?ng lái (Kh?i ngang m?ng phía trên)
    parts.push_back(new TransformShape(Translate(0.4f, 0.35f, zF + 0.01f) * Scale(0.6f, 0.1f, 0.06f), new Cube()));

    // 5. ?ng khói (Kh?i d?c nh? phía tr??c)
    parts.push_back(new TransformShape(Translate(-0.4f, 0.2f, zF) * Scale(0.2f, 0.4f, 0.05f), new Cube()));

    // 6. Bánh xe (3 kh?i nh? màu ?en phía d??i)
    parts.push_back(new TransformShape(Translate(-0.4f, -0.7f, zF) * Scale(0.25f, 0.25f, 0.07f), new Cube()));
    parts.push_back(new TransformShape(Translate(0.0f, -0.7f, zF) * Scale(0.25f, 0.25f, 0.07f), new Cube()));
    parts.push_back(new TransformShape(Translate(0.4f, -0.7f, zF) * Scale(0.25f, 0.25f, 0.07f), new Cube()));
}

PosterQuangCao::~PosterQuangCao() {
    for (auto p : parts) delete p;
}

void PosterQuangCao::draw(const mat4& modelMatrix) const {
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i == 0) Materials::WallPaint.apply();      // N?n Poster tr?ng
        else if (i == 1) Materials::Plastic.apply();    // Thân tàu xanh
        else if (i == 2 || i == 3) Materials::RedToy.apply(); // Bu?ng lái & Mái ??
        else if (i == 4) Materials::Metal.apply();      // ?ng khói xám
        else Materials::ConcreteDark.apply();           // Bánh xe ?en

        parts[i]->draw(modelMatrix);
    }
}