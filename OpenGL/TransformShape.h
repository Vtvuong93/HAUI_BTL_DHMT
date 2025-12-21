#include "Shape.h"
#include "Angel.h"
class TransformShape : public Shape {
private:
    mat4 transform;
    Shape* shape;

public:
    TransformShape(const mat4& t, Shape* s);
    ~TransformShape();

    void draw(const mat4& modelMatrix) const override;

    void initGPUBuffers() override {}  
};
