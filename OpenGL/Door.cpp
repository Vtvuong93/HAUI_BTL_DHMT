#include "Door.h"
#include "TransformShape.h"
#include "MaterialLib.h"

#include "Globals.h"

Door::Door(float w, float h){
    this->h = h;
	// Base
    parts.push_back(
        new TransformShape(
            Translate(0, h / 2 + 0.5f, 0.5f) * 
            Scale(w + 0.05f, 1.0f, 1.0f),
            new Cube()
        )
    );

    // door
    std::cout << "thuc hien lai";
    parts.push_back(
        new TransformShape(
            Scale(w, h, 0.05f),
            new Cube()
        )
    );

}
Door:: ~Door() {
	for (auto p : parts) {
		delete p;
	}
}

void Door::draw(const mat4& modelMatrix) const {
    Materials::Metal.apply();
    parts.at(0)->draw(modelMatrix);
    parts.at(1)->draw(modelMatrix * Translate(0, h * (1 - rolledDoor), 0) * Scale(1.0f, rolledDoor, 1.0f));
}