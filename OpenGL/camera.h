#pragma once
#include "Angel.h"

class Camera {
public:
    // Thuộc tính
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;

    float yaw;
    float pitch;

    float speed;
    float sensitivity;

    // Constructor
    Camera()
        : position(0.0f, 1.5f, 6.0f),
        worldUp(0.0f, 1.0f, 0.0f),
        yaw(-90.0f),
        pitch(0.0f),
        speed(0.7f),
        sensitivity(0.05f)
    {
        updateCameraVectors(); 
    }

    // Hàm public
    mat4 getViewMatrix() const {
        return LookAt(position, position + front, up);
    }

    vec3 getFront() const {
        return front;
    }

    void updateCameraVectors();
};
