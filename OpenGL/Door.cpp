#include "Door.h"
#include "TransformShape.h"
#include "MaterialLib.h"

#include "Globals.h"

Door::Door(float w, float h, mat4 pos0){
    door_w = w;
    door_h = h;
    float thickness = 0.05f;
	// Base
    base_w = door_w * 1.1f, base_h = 1.0;
    base_d = base_h;
    pos = pos0;
    std::cout << pos0;
    parts.push_back(
        new TransformShape(
            Scale(base_w, base_h, base_d),
            new Cube()
        )
    );

    // door
    
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
    mat4 model =  modelMatrix * pos * Translate(0, base_h / 2, 0);
    Materials::ConcreteBeige.apply();
    parts.at(0)->draw(model);
    parts.at(1)->draw(model * 
        Translate(0, door_h * (1 - rolledDoor) / 2, 0) * 
        Translate(0, -door_h / 2 -base_h / 2,- base_d / 2 + thickness) *
        Scale(1.0f, rolledDoor, 1.0f)
    );
}