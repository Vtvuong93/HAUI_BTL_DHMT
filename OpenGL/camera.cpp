#include "camera.h"
#include <cmath>

void Camera::updateCameraVectors() {
    vec3 f;
    float yawRad = yaw * 3.14159265358979323846f / 180.0f;
    float pitchRad = pitch * 3.14159265358979323846f / 180.0f;

    f.x = cos(yawRad) * cos(pitchRad);
    f.y = sin(pitchRad);
    f.z = sin(yawRad) * cos(pitchRad);

    front = normalize(f);
    right = normalize(cross(front, worldUp));
    up = normalize(cross(right, front));
}
