#include "ToyTrain1.h"
#include "TransformShape.h"
#include "ToyLocomotive1.h"
#include "ToyWagon.h"
#include "ToyWagon1.h"

using namespace Angel;

ToyTrain1::ToyTrain1(float s)
{
    /* ===== KÍCH THƯỚC CHUẨN ===== */
    float locoLength = 3.4f * s;
    float wagonLength = 3.4f * s;

    /* ==================================================
       ĐẦU TÀU = GỐC LOCAL (0,0,0)
       ================================================== */
    locomotive = new TransformShape(
        Translate(0.0f, 0.0f, 0.0f),
        new ToyLocomotive1(s)
    );

    /* ==================================================
       TOA 1 – TOA KÍN
       ================================================== */
    wagon1 = new TransformShape(
        Translate(locoLength - 0.12f, 0.0f, 0.0f),
        new ToyWagon(s)
    );

    /* ==================================================
       TOA 2 – TOA HÀNG HỞ
       ================================================== */
    wagon2 = new TransformShape(
        Translate(locoLength + wagonLength, 0.0f, 0.0f),
        new ToyWagon1(s)
    );
}

ToyTrain1::~ToyTrain1()
{
    delete locomotive;
    delete wagon1;
    delete wagon2;
}

void ToyTrain1::draw(const mat4& modelMatrix) const
{
    locomotive->draw(modelMatrix);
    wagon1->draw(modelMatrix);
    wagon2->draw(modelMatrix);
}
