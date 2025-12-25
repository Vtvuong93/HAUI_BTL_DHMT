// Material.h
#pragma once
#include "Angel.h"
typedef vec4 color4;

struct Material {
    color4 ambient;
    color4 diffuse;
    color4 specular;
    float shininess;

    void apply() const;
};
