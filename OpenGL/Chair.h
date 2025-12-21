#include "Shape.h"
#include "Cube.h"
class Chair : public Shape {
private:
    Cube* seat;
    Cube* back;
    Cube* leg1;
    Cube* leg2;
    Cube* leg3;
    Cube* leg4;

public:
    Chair();
    ~Chair();

    void draw(const mat4& modelMatrix) const override;

    void initGPUBuffers() override {}  // 👈 BẮT BUỘC, để trống
};
