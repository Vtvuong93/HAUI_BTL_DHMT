#include "SetPC.h"
#include "TransformShape.h"
#include "MaterialLib.h"
#include <cmath>

SetPC::SetPC(float t_t) {
    float m_w = 1.0f, m_h = 0.75f; 
    float m_t = 0.02f;
    float mg_w = 0.05, mg_t = m_t + 0.01;
    float stand_h = m_h / 2 + 0.2f ;

    float deg = 20;
    mat4 tilt =  RotateX(deg);

    float face = t_t / 2;
    // front face
    parts.push_back(
        new TransformShape(
            tilt * 
            Translate(0, stand_h + face, 0) * 
            Scale(m_w, m_h, m_t),
            new Cube()
        )
    );
    // back side

    parts.push_back(
        new TransformShape(
            tilt *
            Translate(0, stand_h+ face, + 0.005f) *
            Scale(m_w, m_h + mg_w, m_t),
            new Cube()
        )
    );
    // top bar
    parts.push_back(
        new TransformShape(
            tilt *
            Translate(0, stand_h + m_h / 2 + face, - 0.005f) *
            Scale(m_w + mg_w, mg_w, mg_t),
            new Cube()
        )
    );
    parts.push_back(
        new TransformShape(
            tilt *
            Translate(0, stand_h - m_h / 2 + face, -0.005f) *
            Scale(m_w + mg_w, mg_w, mg_t),
            new Cube()
        )
    );
    parts.push_back(
        new TransformShape(
            tilt *
            Translate(-m_w / 2, stand_h + face, -0.005f) *
            Scale(mg_w, m_h + mg_w, mg_t),
            new Cube()
        )
    );
    
    parts.push_back(
        new TransformShape(
            tilt *
            Translate(m_w / 2, stand_h + face, -0.005f) *
            Scale(mg_w, m_h + mg_w, mg_t),
            new Cube()
        )
    );

    // chan man hinh

    parts.push_back(
        new TransformShape(
            Translate(0, stand_h / 2 + face, stand_h * tan(deg / 180 * 3.14) + mg_t / 2) *
            Scale(0.2f, stand_h, mg_t),
            new Cube()
        )
    );
    parts.push_back(
        new TransformShape(
            Translate(0, mg_t / 2 + face, stand_h * tan(deg / 180 * 3.14) + mg_t / 2) *
            Scale(m_w * 0.8f, mg_t, m_h * 0.5f),
            new Cube()
        )
    );
    // ban phim

    parts.push_back(
        new TransformShape(
            Translate(0, mg_t + face, - m_h / 3) *
            Scale(m_w, 2 * mg_t, m_h * 0.5f),
            new Cube()
        )
    );


}
SetPC:: ~SetPC() {
    for (auto p : parts) {
        delete p;
    }
}

void SetPC::draw(const mat4& modelMatrix) const {
    Materials::Plastic.apply();
    parts.at(0)->draw(modelMatrix);

    for (int i = 1; i < parts.size(); i++) {
        Materials::Metal.apply();
        parts.at(i)->draw(modelMatrix);
    }
}