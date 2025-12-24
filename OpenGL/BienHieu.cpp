#include "BienHieu.h"
#include "TransformShape.h"
#include "MaterialLib.h"

using namespace Angel;

BienHieu::BienHieu() {
    float bangW = 4.0f;  // Chieu rong bien
    float bangH = 1.5f;  // Chieu cao bien
    float bangT = 0.2f;  // do dày bien
    float cotH = 2.0f;   // Chieu cao thanh treo

    // 1. M?t bi?n hi?u chính
    parts.push_back(
        new TransformShape(
            Translate(0, 0, 0) * Scale(bangW, bangH, bangT),
            new Cube()
        )
    );

    // 2. Vi?n trang trí phía trên
    parts.push_back(
        new TransformShape(
            Translate(0, bangH / 2 + 0.05f, 0) * Scale(bangW + 0.2f, 0.1f, bangT + 0.05f),
            new Cube()
        )
    );

    // 3. Vi?n trang trí phía d??i
    parts.push_back(
        new TransformShape(
            Translate(0, -(bangH / 2 + 0.05f), 0) * Scale(bangW + 0.2f, 0.1f, bangT + 0.05f),
            new Cube()
        )
    );

    // Vien 2 ben
    parts.push_back(
        new TransformShape(
            Translate(-(bangW/2 + 0.05f), 0, 0) * Scale(0.1f, bangH + 0.2f, bangT + 0.05f),
            new Cube()
        )
	);
    parts.push_back(
        new TransformShape(
            Translate(bangW/2 + 0.05f, 0, 0) * Scale(0.1f, bangH + 0.2f, bangT + 0.05f),
            new Cube()
        )
	);

    // --- THÊM CH? "TOY" (V? b?ng các kh?i Cube nh?) ---
    float netDay = 0.05f; // ?? dày nét ch?
    float chuZ = bangT / 2 + 0.01f; // ??y ch? lên m?t tr??c bi?n hi?u

    // CH? T
    parts.push_back(new TransformShape(Translate(-1.0f, 0.3f, chuZ) * Scale(0.4f, netDay, 0.02f), new Cube())); // Ngang
    parts.push_back(new TransformShape(Translate(-1.0f, 0.0f, chuZ) * Scale(netDay, 0.6f, 0.02f), new Cube())); // D?c

    // CH? O (Ghép t? 4 nét)
    parts.push_back(new TransformShape(Translate(0.0f, 0.3f, chuZ) * Scale(0.4f, netDay, 0.02f), new Cube()));  // Trên
    parts.push_back(new TransformShape(Translate(0.0f, -0.3f, chuZ) * Scale(0.4f, netDay, 0.02f), new Cube())); // D??i
    parts.push_back(new TransformShape(Translate(-0.2f, 0.0f, chuZ) * Scale(netDay, 0.6f, 0.02f), new Cube())); // Trái
    parts.push_back(new TransformShape(Translate(0.2f, 0.0f, chuZ) * Scale(netDay, 0.6f, 0.02f), new Cube()));  // Ph?i

    // CH? Y
    parts.push_back(new TransformShape(Translate(0.8f, -0.15f, chuZ) * Scale(netDay, 0.3f, 0.02f), new Cube())); // Chân d?c
    parts.push_back(new TransformShape(Translate(0.7f, 0.2f, chuZ) * RotateZ(30) * Scale(netDay, 0.4f, 0.02f), new Cube())); // Nhánh trái
    parts.push_back(new TransformShape(Translate(0.9f, 0.2f, chuZ) * RotateZ(-30) * Scale(netDay, 0.4f, 0.02f), new Cube())); // Nhánh ph?i
}

BienHieu::~BienHieu() {
    for (auto p : parts)
        delete p;
}

void BienHieu::draw(const mat4& modelMatrix) const {
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i == 0) {
            Materials::ToyRed.apply(); // N?n bi?n màu ??
        }
        else if (i < 6) {
            Materials::MetalGray.apply();  // Vi?n màu kim lo?i
        }
        else {
            Materials::ConcreteBeige.apply(); // Ch? "TOY" màu vàng nh?t
        }
        parts[i]->draw(modelMatrix);
    }
}